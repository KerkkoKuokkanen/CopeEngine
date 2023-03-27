
#include "Mesh.h"
#include "Tools.h"
#include "Object.h"
#include "Model.h"
#include "Sprite.h"

const unsigned int screenWidth = 1920;
const unsigned int screenHeight = 1080;

float scrollWheel = 0.0f;

float GetDeltaTime(double &startTime, double currentTime)
{
	double ret = currentTime - startTime;
	startTime = currentTime;
	return (ret);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollWheel = (float)yoffset;
}

GLFWwindow *Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // tells what version we are using. Major so opengl 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Same thing but for the minor so x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // tells what package of tools we want

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Engine", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetScrollCallback(window, scroll_callback);
	gladLoadGL(); //Initializes opengl functions so that I can easily use them.
	glViewport(0, 0, screenWidth, screenHeight); //specifies the viewport
	InitDrawLine();
	return (window);
}

void assingLight(Shader &shader)
{
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPosition"), 0.0f, -1.5f, -5.0f);
}

void MakeProjection(Shader &shader)
{
	int viewportWidth, viewportHeight;
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &viewportWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &viewportHeight);
	float aspectRatio = static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
}

int main()
{
	GLFWwindow* window = Init();

	Shader multiCol("default.vert", "default.frag");
	Camera camera(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 2.0f));
	double startTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_CULL_FACE); //this disables the backfaces
	glCullFace(GL_BACK);*/
	assingLight(multiCol);
	Model model("Assets/objects/stem/scene.gltf");
	Shader sprite("sprite.vert", "sprite.frag");
	Texture sideBar("Assets/Sprites/sideBar.png", "tex0", 0);
	Sprite bar(glm::vec2(-1.0f, -1.0f), glm::vec2(0.3f, 2.0f), sideBar, sprite);
	Shader line("line.vert", "line.frag");
	//model.VertTest();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window, GetDeltaTime(startTime, glfwGetTime()), scrollWheel);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);
		
		model.Draw(multiCol, camera);
		bar.Draw(sprite);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
