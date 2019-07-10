#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <glm/glm.hpp>
#include <time.h>

int RandomInt(int, int);
glm::vec3 RandomPosition(int, int, int);

float Random();
glm::vec3 RandomVect();
glm::vec3 RandomUnitVect();
glm::vec3 RandomColor();

float RandomBeetwen(float a, float b);

#endif