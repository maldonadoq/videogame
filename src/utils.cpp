#include "../inc/utils.h"

GLfloat emit[]    = {1.0, 1.0, 1.0, 1.0};
GLfloat no_emit[] = {0.7, 0.7, 0.7, 1.0};

void dibujar_luz(TLuz _l, float _r){	
	glPushMatrix();
		glTranslatef(_l.m_position.x, _l.m_position.y, _l.m_position.z);
     	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);     	
     	glutSolidSphere(_r,15,15);
     	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_emit);  
	glPopMatrix();
}