#include "../inc/jugador.h"

TJugador::TJugador(){

}

TJugador::TJugador(glm::vec3 _pos){
	this->m_posicion = _pos;
	this->m_velocidad_inicial = glm::vec3(0.0f, 10.0f, 0.0f);

	this->m_piso = m_posicion.y;
	this->m_time = 0.0f;
}

TJugador::~TJugador(){
	
}

void TJugador::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TJugador::dibujar(){

}

void TJugador::set_posicion_inicial(){
	this->m_posicion_inicial = m_posicion;
}

glm::vec3 TJugador::get_posicion(){
	return this->m_posicion;
}