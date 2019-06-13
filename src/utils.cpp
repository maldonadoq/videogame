#include "../inc/utils.h"

GLfloat emit[]    = {1.0, 1.0, 1.0, 1.0};

void dibujar_luz(TLuz _l, float _r){	
	glPushMatrix();
		glTranslatef(_l.m_position.x, _l.m_position.y, _l.m_position.z);
     	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
     	glColor3f(1.0f, 1.0f, 1.0f);
     	glutSolidSphere(_r,15,15);
	glPopMatrix();
}

bool cuarto_colision(glm::vec3 _dim, glm::vec3 _centro, glm::vec3 _pos){
	float tx = _dim.x/2;
	float tz = _dim.z/2;
	if(
		((_pos.x > (_centro.x-tx)) and (_pos.x < (_centro.x+tx))) and
		((_pos.y > _centro.y) and (_pos.y < (_centro.y+_dim.y))) and
		((_pos.z > (_centro.z-tz)) and (_pos.z < (_centro.z+tz)))
	){
		return true;
	}

	return false;
}


string vec3_to_str(glm::vec3 _vec){
	return "["+to_string(_vec.x)+","+to_string(_vec.y)+","+to_string(_vec.z)+"]";
}