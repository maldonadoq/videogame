#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "modelo.h"
#include "camara.h"
#include "bala.h"

class TJugador{
public:
	TCamara *m_camara;
	TModelo * m_modelo;
	glm::vec3 m_direccion;

    std::vector<TBala> m_balas;
	float m_dim;

	glm::vec3 m_posicion_inicial;
	glm::vec3 m_velocidad;
	glm::vec3 m_posicion;

	float m_mover;
    int m_vida;
    bool m_saltar;
	float m_piso;

	TJugador(glm::vec3);
	TJugador();
	~TJugador();

	void mover(glm::vec3);
	void anhadir_bala(TBala);

	void dibujar();
	void restart();
	glm::vec3 get_posicion();
	void disparar(float, glm::vec3);
	void barra_vida();
	void set_modelo(TModelo *);
	void set_camara(TCamara *);

	friend std::ostream& operator<< (std::ostream & out, const TJugador &p){
       out << "[" << p.m_posicion.x << "," << p.m_posicion.y << "," << p.m_posicion.z << "]";
       return out;
   	}
};

#endif