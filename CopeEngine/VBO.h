#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

typedef struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texUV;
}				Vertex;

class VBO
{
public:
	GLuint ID;

	void Create(std::vector<Vertex>& vertecies);
	void Bind();
	void Unbind();
	void Delete();
};

#endif
