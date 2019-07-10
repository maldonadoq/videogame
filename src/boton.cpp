#include "../inc/boton.h"

float btno_emit[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float bemit[4] = {0.0f, 0.3f, 0.0f, 1.0f};

TBoton::TBoton(){
	
}

TBoton::TBoton(glm::vec2 _cen, string _text){
	this->center = _cen;
	this->text = _text;
}

TBoton::~TBoton(){

}

void TBoton::dibujar(glm::vec4 _color, glm::vec2 _dim){
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  bemit);
	glColor3f(bemit[0], bemit[1], bemit[2]);

	glBegin(GL_QUADS);
		glVertex3f( center.x + _dim.x, center.y + _dim.y, -2.0f);
		glVertex3f( center.x - _dim.x, center.y + _dim.y, -2.0f);
		glVertex3f( center.x - _dim.x, center.y - _dim.y, -2.0f);
		glVertex3f( center.x + _dim.x, center.y - _dim.y, -2.0f);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  glm::value_ptr(_color));
	glColor3f(_color.x, _color.y, _color.z);
	// int t = (center.y > 0)? -1: 1;
	Font(text, center.x-5, center.y - 1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, btno_emit);
}