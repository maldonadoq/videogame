#ifndef _GESTOR_H_
#define _GESTOR_H_

#include <glm/glm.hpp>
#include "jugador.h"
#include "mapa.h"

class TGestor{
private:
	TJugador *m_jugador;
	TMapa *m_mapa;
	glm::vec3 m_aceleracion;
public:
	TGestor();

	void set_mapa(TMapa *);
	void set_jugador(TJugador *);

	void mover_jugador(glm::vec3);

	void saltar_jugador(float);
	void dibujar_mapa();
	void dibujar_balas_jugador();
	void dibujar_jugador(glm::vec3, float);

	~TGestor();
};

#endif