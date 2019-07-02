#ifndef _MAPA_H_
#define _MAPA_H_

#include <glm/glm.hpp>
#include <assert.h>
#include <FreeImage.h>
#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <utility>

#include "../inc/tmanager.h"
#include "../inc/generar_nivel.h"
#include "cuarto.h"
#include "jugador.h"
#include "puerta.h"

using std::pair;

class TMapa{
private:
	int puerta_textura;
	vector<pair<int, int> > cuarto_texturas;
	glm::vec3 m_centro;
	
	std::vector<std::vector<int> > m_cuartos;
    std::list<ParCoord2D> m_puertas;

	int m_num_niveles = 3;
    int m_anchura = 9;
    int m_altura = 11;
    int m_num_cuartos = 12;
    int m_num_tesoros = 2;
public:
	glm::vec3 m_cuarto_dim;
	TCuarto *m_cuarto_actual;
	std::vector<TCuarto> m_vec_tcuartos;
	std::vector<TPuerta> m_vec_tpuertas;

	TMapa(int, int);
	TMapa();

	void dibujar(float);
	~TMapa();
};

#endif