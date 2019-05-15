#include "../inc/enemigo.h"

TEnemigo::TEnemigo(){

}

TEnemigo::TEnemigo(glm::vec3 _pos){
	this->m_posicion = _pos;
	this->m_velocidad_inicial = glm::vec3(0.0f, 5.0f, 0.0f);

	this->m_piso = m_posicion.y;
	this->m_time = 0.0f;
    this->m_vida = 5;
}

TEnemigo::~TEnemigo(){
	
}

void TEnemigo::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TEnemigo::dibujar(){

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