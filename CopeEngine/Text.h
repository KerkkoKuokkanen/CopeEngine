#ifndef TEXT_H
#define TEXT_H

#include "Mesh.h"
#include "Sprite.h"

class Text
{
private:
	Sprite *atlas;
public:
	Text(Shader &shader);
};

#endif