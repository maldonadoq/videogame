#ifndef _GESTOR_H_
#define _GESTOR_H_

#include <glm/glm.hpp>
#include "jugador.h"
#include "enemigo.h"
#include "mapa.h"
#include "random.h"
#include "modelo.h"
#include "ovni.h"
#include "monstruo.h"
#include <glm/gtc/type_ptr.hpp>

using std::cout;
using std::vector;

class TGestor{
private:
	float m_dt;
	TJugador *m_jugador;
	vector<TEnemigo *> m_enemigos;
	vector<TModelo *> m_muebles;
	TMapa *m_mapa;

	glm::vec3 m_fuerza;
public:
	TGestor();

	void set_mapa(TMapa *);
	void set_jugador(TJugador *);
	void crear_enemigos(unsigned);

	void mover_jugador(glm::vec3);
	void saltar_jugador();
	
	void dibujar_mapa();
	void dibujar_balas_jugador();
	void dibujar_jugador(glm::vec3);
	void dibujar_enemigos();

	void set_dt(float);
	~TGestor();
};

#endif