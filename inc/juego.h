#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <irrKlang.h>
using namespace irrklang;

#include "listen.h"
#include "mapa.h"
#include "camara.h"
#include "utils.h"
#include "gestor.h"
#include "jugador.h"
#include "enemigo.h"
#include "boton.h"
#include "tmanager.h"

#include <iostream>
#include <chrono>
#include <thread>

enum teclas{
	ESC 	= 27,	// terminar el juego
	SPACE	= ' ',	// saltar
	Q		= 'q',	// primera o tercer persona
	C 		= 'c',	// mostrar la dimension de la colision
    L       = 'l',  // leyenda del jugador
    E       = 'e',	// abrir puerta
    W 		= 'w',	// arrodillarse
    ENTER	= 13, 	// disparar
    TAB     = 9		// cambiar de arma
};

class TJuego{
private:
	void initGL();

	static glm::vec3 m_etime;
	glm::vec3 m_mouse;

	GLsizei m_ancho;
	GLsizei m_alto;

	int   m_origen;
	int filas, columnas;
	
	static TJugador *m_jugador;
	static TGestor *m_gestor;
	static vector<TBoton> m_botons;
	static TMapa *m_mapa;

	int m_num_niveles;
	int m_cont_n_niveles;

	int menu_tid;

	static bool salio;

	static void leap_gesture();
	void dibujar_juego();
	void dibujar_ui();

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