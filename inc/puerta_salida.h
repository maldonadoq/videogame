#ifndef _PUERTA_SALIDA_H_
#define _PUERTA_SALIDA_H_

#include <glm/glm.hpp>
#include <FreeImage.h>
#include <GL/glut.h>
#include <list>
#include "cuarto.h"
#include "orient.h"

class TCuarto;


class TPuertaSalida{
public:
    glm::vec3 m_centro;
    glm::vec2 m_dim;
    Orientacion m_orient;
    TCuarto* m_cuarto1;

	TPuertaSalida(glm::vec3, glm::vec2, Orientacion, TCuarto*);
	TPuertaSalida();

	void dibujar(int);
};

#endif