#ifndef _GESTOR_H_
#define _GESTOR_H_

#include <glm/glm.hpp>
#include "jugador.h"
#include "enemigo.h"	
#include "mapa.h"
#include "random.h"
#include "modelo.h"
#include <glm/gtc/type_ptr.hpp>

class TGestor{
private:
	TPersona *m_jugador;
	std::vector<TEnemigo *> m_enemigos;
	TMapa *m_mapa;

	std::vector<TModelo *> m_modelos;

	glm::vec3 m_aceleracion;
public:
	TGestor();

	void set_mapa(TMapa *);
	void set_jugador(TJugador *);
	void crear_enemigos(unsigned);

	void mover_jugador(glm::vec3);
	void mover_enemigos();

	void saltar_jugador(float);
	
	void dibujar_mapa();
	void dibujar_balas_jugador();
  
	void dibujar_jugador(glm::vec3, float);	
	void dibujar_enemigos();
  
  	void dibujar_balas_enemigo();
  	void dibujar_enemigo(glm::vec3,float);

	~TGestor();
};

#endif