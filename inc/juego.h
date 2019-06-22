#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mapa.h"
#include "camara.h"
#include "utils.h"
#include "gestor.h"
#include "audio.h"
#include "jugador.h"
#include "enemigo.h"

#include <iostream>

enum teclas{
	ESC = 27,
	SPACE = ' ',
	UP = 'u',
	FIRST = 'f',
	A = 'a',
	L = 'l'//leyenda del jugador
};

class TJuego{
private:
	void initGL();

	TAudio *m_audio;
	glm::vec3 m_etime;
	glm::vec3 m_mouse;

	GLsizei m_ancho;
	GLsizei m_alto;

	int   m_origen;
	int filas, columnas;	
	
	TJugador *m_jugador;
	TGestor *m_gestor;
	TMapa *m_mapa;
public:
	TJuego(int &, char **);
	virtual ~TJuego();

	void dibujar();
	void remodelar(GLsizei, GLsizei);
	void presionar_tecla(unsigned char, int, int);
	void presionar_tecla_especial(int, int, int);
	void soltar_tecla_especial(int, int, int);
	void mouse(int, int, int, int);
	void mouse_motion(int, int);

	TLuz m_luz;
	TCamara *m_camara;
};

#endif