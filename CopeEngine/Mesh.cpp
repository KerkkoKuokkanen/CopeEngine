
#include "Mesh.h"

void Mesh::CalculateNormals()
{
	for (int i = 0; i < indecies.size(); i += 3)
	{
		glm::vec3 v1 = vertecies[indecies[i]].position;
		glm::vec3 v2 = vertecies[indecies[i + 1]].position;
		glm::vec3 v3 = vertecies[indecies[i + 2]].position;
		glm::vec3 edge1 = v2 - v1;
		glm::vec3 edge2 = v3 - v1;
		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));
		vertecies[indecies[i]].normal = normal;
		vertecies[indecies[i + 1]].normal = normal;
		vertecies[indecies[i + 2]].normal = normal;
	}
}

void Mesh::CreateMesh(std::vector<Vertex>& vertecies, std::vector<GLuint>& indecies, std::vector<Texture> &textures)
{
	Mesh::vertecies = vertecies;
	Mesh::indecies = indecies;
	Mesh::textures = textures;

	VAO.Bind();

	VBO.Create(Mesh::vertecies);
	EBO.Create(Mesh::indecies);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader &shader, Camera& camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
{
	shader.Activate();
	VAO.Bind();
	
	unsigned int numDiffuse = 0, numSpecular = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
			num = std::to_string(numDiffuse++);
		else if (type == "specular")
			num = std::to_string(numSpecular++);
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
}

void ChangeColor(Mesh *mesh, glm::vec3 color)
{
	mesh->VAO.Bind();
	mesh->VBO.Bind();

	Vertex* vertData = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < mesh->vertecies.size(); i++)
		vertData[i].color = color;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	mesh->VBO.Unbind();
	mesh->VAO.Unbind();
}

void ChangeBack(Mesh* mesh)
{
	mesh->VAO.Bind();
	mesh->VBO.Bind();

	Vertex* vertData = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < mesh->vertecies.size(); i++)
		vertData[i].color = mesh->vertecies[i].color;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	mesh->VBO.Unbind();
	mesh->VAO.Unbind();
}

void Mesh::GetLight(glm::vec3 lightDir)
{
	glm::vec3 light = glm::normalize(lightDir);

	for (int i = 0; i < vertecies.size(); i++)
	{
		float dp = vertecies[i].normal.x * light.x + vertecies[i].normal.y * light.y + vertecies[i].normal.z * light.z;
		float col = glm::max(1.0f * dp, 0.1f);
		vertecies[i].color.x = col;
		vertecies[i].color.y = col;
		vertecies[i].color.z = col;
	}
}

void Mesh::SetColor()
{
	VAO.Bind();
	VBO.Bind();

	Vertex* vertData = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	for (int i = 0; i < vertecies.size(); i++)
	{
		vertData[i].color = vertecies[i].color;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	VBO.Unbind();
	VAO.Unbind();
}

void Mesh::Move(glm::vec3 to, Shader &shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, to);
	currPos = to;
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

void Mesh::DrawLines(Camera& camera, glm::vec3 color, Shader &shader)
{
	ChangeColor(this, color);
	shader.Activate();
	VAO.Bind();
	camera.Matrix(shader, "camMatrix");
	glDrawElements(GL_LINES, indecies.size(), GL_UNSIGNED_INT, 0);
	SetColor();
	//lightColor(glm::vec3(0.0f, 0.0f, 1.0f), this); //need to come back to this to optimize later
}

void Mesh::Delete()
{
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
}