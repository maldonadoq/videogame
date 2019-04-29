#ifndef _MAPA_H_
#define _MAPA_H_

#include <vector>
#include <glm/glm.hpp>
#include "cuarto.h"

class TMapa{
private:
	TCuarto *m_cuarto_actual;
	int texturas_id[2];
public:
	TMapa(int, int);
	TMapa();

	void dibujar();

	~TMapa();
};

#endif