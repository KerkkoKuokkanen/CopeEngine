#include "Tools.h"

std::vector<Vertex> vert;


typedef struct sLine
{
	glm::vec3 point;
	glm::vec3 color;
}				tLine;

void InitDrawLine()
{
	vert.reserve(2);
}

void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color, Camera& camera, Shader& shader)
{
	Vertex one = { start, color, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	Vertex two = { end, color, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vert.clear();
	vert.push_back(one);
	vert.push_back(two);
	std::vector<GLuint> ind = { 0, 1 };
	Mesh mesh;
	std::vector<Texture> tex;
	mesh.CreateMesh(vert, ind, tex);
	mesh.DrawLines(camera, color, shader);
	mesh.Delete();
}
