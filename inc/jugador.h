#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "persona.h"

class TJugador: public TPersona{	
public:
	TJugador(glm::vec3);
	TJugador();
	~TJugador();

	void mover(glm::vec3);
	void anhadir_bala(TBala);

	void dibujar();
	void set_posicion_inicial();
	glm::vec3 get_posicion();
};

#endif