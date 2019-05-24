#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <glm/glm.hpp>

int RandomInt(int, int);
glm::vec3 RandomPosition(int, int, int);

float Random();
glm::vec3 RandomVect();
glm::vec3 RandomColor();

#endif