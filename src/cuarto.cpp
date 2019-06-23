/*
Contiene toda la informacion relacionada con un cuarto,
como dibujarlo, las posiciones de las paredes y suelo, y
tambien una funcion para detectar colision del personaje con
el cuarto.
*/

#include "../inc/cuarto.h"

TCuarto::TCuarto(){
	this->m_centro = glm::vec3(0,0,0);
	this->m_dim = glm::vec3(10,5,10);
	this->m_escala = m_dim/5.0f;
	this->m_jugador = NULL;
	this->m_enemigos.clear();
	this->m_items.clear();

	this->m_colision = true;
}

TCuarto::TCuarto(glm::vec3 _centro, glm::vec3 m_dim){
	this->m_centro = _centro;
	this->m_dim = m_dim;
	this->m_escala = m_dim/10.0f;
	this->m_jugador = NULL;
	this->m_enemigos.clear();
	this->m_items.clear();

	this->m_colision = true;
}

void TCuarto::dibujar_paredes(){

	float tx = m_dim.x/2;
	float tz = m_dim.z/2;

	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		// z-y
		// glTexCoord2f(1.0f, 1.0f);
		glTexCoord2f(m_escala.z, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z - tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z + tz);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z + tz);
		
		glTexCoord2f(m_escala.z, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z - tz);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		
		glTexCoord2f(m_escala.z, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z + tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z - tz);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z - tz);
		
		glTexCoord2f(m_escala.z, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z + tz);				
	glEnd();

	// x-y
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		
		glTexCoord2f(m_escala.x, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z -tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z -tz);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z -tz);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z -tz);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		
		glTexCoord2f(m_escala.x, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z +tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z +tz);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z +tz);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z +tz);
	glEnd();
}

void TCuarto::dibujar_piso(){
	float tx = m_dim.x/2;
	float tz = m_dim.z/2;
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		// x-z
		glTexCoord2f(m_escala.x, m_escala.z);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z + tz);
		
		glTexCoord2f(0.0f, m_escala.z);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z - tz);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z - tz);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z + tz);
	glEnd();
}

void TCuarto::dibujar(int _tf, int _tw, float _dt){
	glBindTexture(GL_TEXTURE_2D, _tf);
	dibujar_piso();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, _tw);
	dibujar_paredes();
	glBindTexture(GL_TEXTURE_2D, 0);


	if(m_jugador != NULL){
		dibujar_enemigos(_dt);
		dibujar_items();
	}
}

void TCuarto::set_enemigo(TEnemigo *_enemigo){
	_enemigo->m_posicion += m_centro;
	// std::cout << "pos en: " << vec3_to_str(_enemigo->m_posicion) << "\n";
	this->m_enemigos.push_back(_enemigo);
}

void TCuarto::set_item(TItem *_item){
	_item->m_posicion += m_centro;
	// std::cout << "pos it: " << vec3_to_str(_item->m_posicion) << "\n";
	this->m_items.push_back(_item);
}

void TCuarto::set_jugador(TJugador *_jugador){
	assert(_jugador != NULL);
	_jugador->m_posicion += m_centro;
	// std::cout << "pos ju: " << vec3_to_str(_jugador->m_posicion) << "\n";
	this->m_jugador = _jugador;
}

void TCuarto::dibujar_items(){
	for(unsigned i=0; i<m_items.size(); i++){
		m_items[i]->dibujar(m_colision);
	}
}

void TCuarto::dibujar_enemigos(float _dt){
	for(unsigned i=0; i<m_enemigos.size(); i++){
		m_enemigos[i]->mover(m_jugador->m_posicion, m_dim, m_centro, _dt);
		m_enemigos[i]->dibujar(m_dim, m_centro, m_colision);
		m_enemigos[i]->barra_vida(m_jugador->m_posicion);
		m_enemigos[i]->cargar(_dt);
	}
}

TCuarto::~TCuarto(){

}