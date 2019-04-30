#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>

class TJugador{
private:	
public:
	glm::vec3 m_posicion;	
	glm::vec3 m_dim;	

	glm::vec3 m_posicion_inicial;
	glm::vec3 m_velocidad_inicial;

	float m_piso;
	float m_time;

	bool m_saltar;
	float m_mover;

	TJugador(glm::vec3);
	TJugador();
	~TJugador();

	void mover(glm::vec3);
	void dibujar();

	void set_posicion_inicial();

	glm::vec3 get_posicion();
};

#endif