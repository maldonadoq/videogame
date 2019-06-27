#ifndef _GESTOR_H_
#define _GESTOR_H_

#include <glm/glm.hpp>
#include "jugador.h"
#include "enemigo.h"
#include "mapa.h"
#include "random.h"
#include "modelo.h"
#include "item.h"
#include "utils.h"
#include "ovni.h"
#include "hydra.h"
#include "monstruo.h"
#include "sentinel.h"
#include "motor.h"
#include <glm/gtc/type_ptr.hpp>

using std::cout;
using std::vector;

class TGestor{
private:
	int m_fuego_textura;
	float m_dt;
	TJugador *m_jugador;
	std::map<std::string ,TModelo *> m_modelos;
	TMapa *m_mapa;

	glm::vec3 m_fuerza;

	vector<TMotor *> m_efectos;
public:
	TGestor();

	void set_mapa(TMapa *);
	void set_jugador(TJugador *);
	void init();

	void mover_jugador(glm::vec3);
	void saltar_jugador();
	void arrodillarse_jugador(bool);
	
	void dibujar_mapa();
	void dibujar_balas_jugador();
	void dibujar_jugador(glm::vec3);
	void dibujar_leyenda();
	void dibujar_efectos();

	void set_dt(float);
	~TGestor();
};

#endif