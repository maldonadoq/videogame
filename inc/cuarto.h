#ifndef _CUARTO_H_
#define _CUARTO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include "jugador.h"
#include "enemigo.h"
#include "item.h"
#include <vector>

using std::vector;

class TCuarto{
private:
	glm::vec3 m_escala;
public:
	glm::vec3 m_centro;	// 0,0,0
	glm::vec3 m_dim;	// x,y,z
	vector<TItem *> m_items;
	vector<TEnemigo *> m_enemigos;
	TJugador *m_jugador;

	bool m_colision;

	TCuarto(glm::vec3, glm::vec3);
	TCuarto();
	virtual ~TCuarto();

	void actualizar();
	void dibujar(int, int, float);

	void set_jugador(TJugador *);
	void set_item(TItem *);
	void set_enemigo(TEnemigo *);

	void dibujar_enemigos(float);
	void dibujar_items();

	void dibujar_paredes();
	void dibujar_piso();
};

#endif