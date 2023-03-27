//256, 96

#include "Text.h"

Text::Text(Shader &shader)
{
	Texture font("Assets/Sprites/font.png", "tex0", 0);
	static Sprite atlas(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), font, shader);
	Text::atlas = &atlas;
}