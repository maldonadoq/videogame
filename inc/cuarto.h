#ifndef _CUARTO_H_
#define _CUARTO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include "jugador.h"

class TCuarto{
private:	
	glm::vec3 m_escala;
public:
	glm::vec3 m_centro;	// 0,0,0
	glm::vec3 m_dim;	// x,y,z
	bool m_state;

	TCuarto(glm::vec3, glm::vec3);
	TCuarto();
	virtual ~TCuarto();

	void actualizar();
	void dibujar(int, int);

	void dibujar_paredes();
	void dibujar_piso();
};

#endif