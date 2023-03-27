#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color, Camera& camera, Shader& shader);
void InitDrawLine();

#endif
