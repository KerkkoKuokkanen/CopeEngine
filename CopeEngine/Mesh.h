#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"
#include "shaderClass.h"

class Mesh
{
public:
	std::vector<Vertex> vertecies;
	std::vector<GLuint> indecies;
	std::vector<Texture> textures;
	glm::vec3 currPos = glm::vec3(0.0f, 0.0f, 0.0f);
	VAO VAO;
	VBO VBO;
	EBO EBO;

	void CreateMesh(std::vector<Vertex>& vertecies, std::vector<GLuint>& indecies, std::vector<Texture> &textures);
	void CalculateNormals();
	void Draw(Shader &shader, Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	void DrawLines(Camera& camera, glm::vec3 color, Shader &shader);
	void GetLight(glm::vec3 lightDir);
	void SetColor();
	void Move(glm::vec3 to, Shader &shader);
	void Delete();
};

#endif
