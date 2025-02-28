#ifndef _CUARTO_H_
#define _CUARTO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>
#include "jugador.h"
#include "enemigo.h"
#include "item.h"
#include "puerta.h"
#include "puerta_salida.h"
#include <string>

using std::vector;
using std::list;

class TPuerta;
class TPuertaSalida;

class TCuarto{
private:
	glm::vec3 m_escala;
public:
	glm::vec3 m_centro;	// 0,0,0
	glm::vec3 m_dim;	// x,y,z
	vector<TItem *> m_items;
	vector<TEnemigo *> m_enemigos;
	TJugador *m_jugador;
	list<TPuerta *> m_puertas;
	std::string m_tipo;
	TPuertaSalida *m_puerta_salida;

	bool m_colision;

	TCuarto(glm::vec3, glm::vec3, std::string);
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

	bool verificar_puertas(TJugador*, TCuarto**, bool&);
};

#endif