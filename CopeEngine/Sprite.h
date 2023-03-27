#ifndef SPRITE_H
#define SPRITE_H

#include "Mesh.h"

class Sprite
{
private:
	Mesh mesh;
public:
	Sprite(glm::vec2 pos, glm::vec2 dim, Texture &sprite, Shader &shader);
	void Draw(Shader &shader);
	void DrawRect(Shader& shader, glm::vec4 dest, glm::vec4 rect);
};

#endif