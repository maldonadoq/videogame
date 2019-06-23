#ifndef _PUERTA_H_
#define _PUERTA_H_

#include <glm/glm.hpp>
#include <FreeImage.h>
#include <GL/glut.h>
#include <list>

enum Orientacion{
	x,
    z
};

class TPuerta{
public:
    glm::vec3 m_centro;
    glm::vec2 m_dim;
    Orientacion m_orient;

	TPuerta(glm::vec3, glm::vec2, Orientacion);
	TPuerta();

	void dibujar(int);
};

#endif