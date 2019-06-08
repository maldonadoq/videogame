#ifndef _MAPA_H_
#define _MAPA_H_

#include <glm/glm.hpp>
#include <assert.h>
#include <FreeImage.h>
#include <iostream>
#include <vector>
#include <random>
#include <list>

#include "../inc/tmanager.h"
#include "../inc/generar_nivel.h"
#include "cuarto.h"
#include "jugador.h"
#include "puerta.h"


class TMapa{
private:
	int texturas_id[15];
	glm::vec3 m_centro;
	
	std::vector<std::vector<int> > m_cuartos;
    std::list<ParCoord2D> m_puertas;

	int m_num_niveles = 3;
    int m_anchura = 9;
    int m_altura = 11;
    int m_num_cuartos = 7;
    int m_num_tesoros = 2;
public:
	glm::vec3 m_cuarto_dim;
	TCuarto *m_cuarto_actual;
	std::vector<TCuarto> m_vec_tcuartos;
	std::vector<TPuerta> m_vec_tpuertas;

	TMapa(int, int);
	TMapa();

	void dibujar();
	void dibujar_cuartos();

	~TMapa();
};

#endif