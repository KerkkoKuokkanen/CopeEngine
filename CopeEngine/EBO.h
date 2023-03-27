#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;

	void Create(std::vector<GLuint>& indecies);
	void Bind();
	void Unbind();
	void Delete();
};

#endif
