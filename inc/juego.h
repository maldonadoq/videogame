#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include "utils.h"
#include "mapa.h"
#include "camara.h"

#include <iostream>

enum teclas{
	ESC = 27,
	A = 'a'
};

class TJuego{
private:
	void initGL();

	glm::vec3 m_etime;
	glm::vec3 m_delta;
	glm::vec3 m_mouse;

	GLsizei m_ancho;
	GLsizei m_alto;

	int filas, columnas;	
	// TJugador *m_jugador;	
	TMapa *m_mapa;

public:
	TJuego(int &, char **);
	virtual ~TJuego();

	void dibujar();
	void remodelar(GLsizei, GLsizei);
	void tecla_presionada(unsigned char, int, int);
	void mouse(int, int, int, int);
	void mouse_motion(int, int);

	TLuz m_luz;
	TCamara *m_camara;
};

#endif