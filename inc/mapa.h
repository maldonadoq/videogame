#ifndef _MAPA_H_
#define _MAPA_H_

#include <glm/glm.hpp>
#include <assert.h>
#include <FreeImage.h>
#include <iostream>
#include <vector>

#include "../inc/tmanager.h"
#include "cuarto.h"
#include "jugador.h"

enum textures_name{
	tfloor,
	twall,
	tfront,
	tback,
	tleft,
	tright,
	tup,
	tdown
};

class TMapa{
private:
	int texturas_id[8];
	glm::vec3 m_mundo_dim;	
	glm::vec3 m_centro;
	glm::vec3 m_temp;
public:
	glm::vec3 m_cuarto_dim;
	TCuarto *m_cuarto_actual;

	TMapa(int, int);
	TMapa();

	void dibujar();
	void dibujar_mundo();

	~TMapa();
};

#endif