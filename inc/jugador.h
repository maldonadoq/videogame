#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <vector>
#include "utils.h"
#include "modelo.h"
#include "camara.h"
#include "bala.h"

enum TArma{
	asimple = 0,
	adoble = 1,
	areloj = 2,
	arebote = 3
};

class TJugador{
private:
	bool armas[4];
	int m_arma;
public:
	TCamara *m_camara;
	TModelo *m_modelo;

    std::vector<TBala *> m_balas;

	glm::vec3 m_velocidad;
	glm::vec3 m_posicion;

	float m_mover;
    int m_vida;
	float m_piso;
	int m_accion;
	bool m_llave;

	TJugador(glm::vec3);
	TJugador();
	~TJugador();

	void mover(glm::vec3);

	void dibujar();
	glm::vec3 get_posicion();
	void disparar(glm::vec3, float);
	void set_modelo(TModelo *);
	void set_camara(TCamara *);
	bool colision(glm::vec3, float);
	void cambiar_arma();
	void set_arma(int);
	string get_arma();
	string get_llave();

	friend std::ostream& operator<< (std::ostream & out, const TJugador &p){
       out << "[" << p.m_posicion.x << "," << p.m_posicion.y << "," << p.m_posicion.z << "]";
       return out;
   	}
};

#endif