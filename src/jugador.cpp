#include "../inc/jugador.h"

TJugador::TJugador(){

}

TJugador::TJugador(glm::vec3 _pos){
	this->m_posicion = _pos;
	this->m_vida = 5;
	this->m_piso = m_posicion.y;
	this->m_dim = 5;
	this->m_mover = 0.0f;
}

TJugador::~TJugador(){
	
}

void TJugador::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TJugador::dibujar(){
	/*glPushMatrix();
		glRotatef(m_camara->m_direccion.x, 1, 0, 0);
		glRotatef(m_camara->m_direccion.z, 0, 0, 1);
		glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
		m_modelo->dibujar();
	glPopMatrix();*/
}

void TJugador::barra_vida(){
	
}

void TJugador::set_modelo(TModelo *_model){
	this->m_modelo = _model;
}

void TJugador::set_camara(TCamara *_camara){
	this->m_camara = _camara;
}

void TJugador::restart(){
	this->m_posicion_inicial = m_posicion;
	this->m_velocidad = glm::vec3(0.0f, 10.0f, 0.0f);

}

glm::vec3 TJugador::get_posicion(){
	return this->m_posicion;
}

void TJugador::disparar(float _x, glm::vec3 _v){

}

void TJugador::anhadir_bala(TBala _bala){
	this->m_balas.push_back(_bala);
}