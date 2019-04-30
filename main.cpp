#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "inc/juego.h"

TJuego *juego;

int main(int argc, char *argv[]){
	juego = new TJuego(argc, argv);

	glutDisplayFunc([](){
		juego->dibujar();
	});
    glutReshapeFunc([](GLsizei w, GLsizei h){
        juego->remodelar(w, h);
    });

    glutIdleFunc([](){
        glutPostRedisplay();
    });

    glutKeyboardFunc([](unsigned char c, int x, int y) {
        juego->presionar_tecla(c, x, y);
    });

    glutSpecialUpFunc([](int c, int x, int y){
        juego->soltar_tecla_especial(c,x,y);
    });

    glutSpecialFunc([](int c, int x, int y) {
        juego->presionar_tecla_especial(c, x, y);
    });

    glutMouseFunc([](int b, int s, int x, int y){
    	juego->mouse(b,s,x,y);
    });

	glutMotionFunc([](int x, int y){
		juego->mouse_motion(x,y);
	});    

	glutMainLoop();

	delete juego;
	return 0;
}