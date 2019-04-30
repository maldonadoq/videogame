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

class TMapa{
private:
	int texturas_id[2];
public:
	TCuarto *m_cuarto_actual;

	TMapa(int, int);
	TMapa();

	void dibujar();

	~TMapa();
};

#endif