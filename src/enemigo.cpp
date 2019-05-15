#include "../inc/enemigo.h"

TEnemigo::TEnemigo(){

}

TEnemigo::TEnemigo(glm::vec3 _pos): TPersona(_pos){
	this->m_velocidad_inicial = glm::vec3(0.0f, 5.0f, 0.0f);
    this->m_vida = 5;
}

TEnemigo::~TEnemigo(){
}

void TEnemigo::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TEnemigo::dibujar(){
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
	
	//cuerpo	
	glTranslatef(0.0f ,0.0f, 0.0f);
	glutSolidSphere(4,20,20);

	//cabeza
	glTranslatef(0.0f, 5.5f, 0.0f);
	glutSolidSphere(2,20,20);

	//nariz
	glColor3f(1.0f, 0.5f , 0.5f);
	glTranslatef(0.0f, 0.0f, 2.0f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.5f, 2.0f,10,2);
}

void TEnemigo::set_posicion_inicial(){
	this->m_posicion_inicial = m_posicion;
}

glm::vec3 TEnemigo::get_posicion(){
	return this->m_posicion;
}

void TEnemigo::anhadir_bala(TBala _bala){
	this->m_balas.push_back(_bala);
}