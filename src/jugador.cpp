#include "../inc/jugador.h"

TJugador::TJugador(){

}

TJugador::TJugador(glm::vec3 _pos): TPersona(_pos){
	this->m_posicion = _pos;
	this->m_velocidad_inicial = glm::vec3(0.0f, 15.0f, 0.0f);

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

void TJugador::anhadir_bala(TBala _bala){
	this->m_balas.push_back(_bala);
}