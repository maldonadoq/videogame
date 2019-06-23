#ifndef _PUERTA_H_
#define _PUERTA_H_

#include <glm/glm.hpp>
#include <FreeImage.h>
#include <GL/glut.h>
#include <list>
#include "cuarto.h"

class TCuarto;

enum Orientacion{
	x,
    z
};

class TPuerta{
public:
    glm::vec3 m_centro;
    glm::vec2 m_dim;
    Orientacion m_orient;
    TCuarto* m_cuarto1;
    TCuarto* m_cuarto2;

	TPuerta(glm::vec3, glm::vec2, Orientacion, TCuarto*, TCuarto*);
	TPuerta();

	void dibujar(int);
};

#endif