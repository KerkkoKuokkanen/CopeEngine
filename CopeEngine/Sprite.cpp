#include "Sprite.h"

Sprite::Sprite(glm::vec2 pos, glm::vec2 dim, Texture &sprite, Shader &shader)
{
	Vertex vert1 = { glm::vec3(pos.x, pos.y, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };
	Vertex vert2 = { glm::vec3(pos.x, pos.y + dim.y, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	Vertex vert3 = {
		glm::vec3(pos.x + dim.x, pos.y + dim.y, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};
	Vertex vert4 = {
		glm::vec3(pos.x + dim.x, pos.y, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f)
	};
	GLuint index[] = {
		0, 1, 3,
		1, 2, 3
	};
	std::vector<GLuint> ind(index, index + sizeof(index) / sizeof(GLuint));
	std::vector<Vertex> verts;
	verts.push_back(vert1);
	verts.push_back(vert2);
	verts.push_back(vert3);
	verts.push_back(vert4);
	std::vector<Texture> text;
	sprite.texUnit(shader, "tex0", 0);
	text.push_back(sprite);
	mesh.CreateMesh(verts, ind, text);
}

void Sprite::Draw(Shader &shader)
{
	if (mesh.textures.size() == 0)
		return;
	glDisable(GL_DEPTH_TEST);
	shader.Activate();
	mesh.VAO.Bind();
	mesh.textures[0].Bind();
	mesh.textures[0].texUnit(shader, "tex0", 0);
	glDrawElements(GL_TRIANGLES, mesh.indecies.size(), GL_UNSIGNED_INT, 0);
	glEnable(GL_DEPTH_TEST);
}

void Sprite::DrawRect(Shader& shader, glm::vec4 dest, glm::vec4 rect)
{
	mesh.VAO.Bind();
	mesh.VBO.Bind();
	Vertex* vertData = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	vertData[0].position = glm::vec3(dest.x, dest.y + dest.w, 0.0f);
	vertData[0].texUV = glm::vec2(rect.x, rect.y + rect.w);
	vertData[1].position = glm::vec3(dest.x, dest.y, 0.0f);
	vertData[1].texUV = glm::vec2(rect.x, rect.y);
	vertData[2].position = glm::vec3(dest.x + dest.z, dest.y, 0.0f);
	vertData[2].texUV = glm::vec2(rect.x + rect.z, rect.y);
	vertData[3].position = glm::vec3(dest.x + dest.z, dest.y + dest.w, 0.0f);
	vertData[3].texUV = glm::vec2(rect.x + rect.z, rect.y + rect.w);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glDisable(GL_DEPTH_TEST);
	shader.Activate();
	mesh.VAO.Bind();
	mesh.textures[0].Bind();
	mesh.textures[0].texUnit(shader, "tex0", 0);
	glDrawElements(GL_TRIANGLES, mesh.indecies.size(), GL_UNSIGNED_INT, 0);
	glEnable(GL_DEPTH_TEST);
	mesh.VAO.Bind();
	mesh.VBO.Bind();
	Vertex* vertData2 = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	vertData2[0].position = mesh.vertecies[0].position;
	vertData2[0].texUV = mesh.vertecies[0].texUV;
	vertData2[1].position = mesh.vertecies[1].position;
	vertData2[1].texUV = mesh.vertecies[1].texUV;
	vertData2[2].position = mesh.vertecies[2].position;
	vertData2[2].texUV = mesh.vertecies[2].texUV;
	vertData2[3].position = mesh.vertecies[3].position;
	vertData2[3].texUV = mesh.vertecies[3].texUV;
	glUnmapBuffer(GL_ARRAY_BUFFER);
}
