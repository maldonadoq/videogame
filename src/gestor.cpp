#include "../inc/gestor.h"

TGestor::TGestor(){
	this->m_jugador = NULL;
	this->m_mapa = NULL;
	this->m_aceleracion = glm::vec3(0.0f, -9.81f, 0.0f);
}

void TGestor::set_mapa(TMapa *_mapa){
	this->m_mapa = _mapa;
}

void TGestor::set_jugador(TJugador *_jugador){
	this->m_jugador = _jugador;
}

void TGestor::dibujar_mapa(){
	this->m_mapa->dibujar();
}

void TGestor::saltar_jugador(float _dt){
	if(m_jugador->m_saltar){
		m_jugador->m_time += _dt;

		m_jugador->m_posicion = 
			m_jugador->m_posicion_inicial +
			(m_jugador->m_velocidad_inicial*m_jugador->m_time) + 
			(m_aceleracion*(float)pow(m_jugador->m_time,2)*0.5f);

		if(m_jugador->m_posicion.y < m_jugador->m_piso){
			m_jugador->m_saltar = false;
			m_jugador->m_time = 0;
			m_jugador->m_posicion.y = m_jugador->m_piso;
		}
	}
}

void TGestor::dibujar_balas_jugador(){
	unsigned i;

	// dibujar las balas
	glColor3f(0.0f, 1.0f, 0.0f);
	for(i=0; i<m_jugador->m_balas.size(); i++){
		glPushMatrix();
			glTranslatef(
				m_jugador->m_balas[i].m_posicion.x,
				m_jugador->m_balas[i].m_posicion.y,
				m_jugador->m_balas[i].m_posicion.z
			);

			glutSolidSphere(m_jugador->m_balas[i].m_radio,8,8);
		glPopMatrix();

		m_jugador->m_balas[i].m_posicion += m_jugador->m_balas[i].m_direccion;

		if(!m_mapa->m_cuarto_actual->colision_paredes(
			m_jugador->m_balas[i].m_posicion)){
			
			m_jugador->m_balas.erase(m_jugador->m_balas.begin()+i);
			i--;
		}
	}
}

void TGestor::dibujar_jugador(glm::vec3 _dir, float _dt){
	if(m_jugador->m_mover){
		mover_jugador(_dir*m_jugador->m_mover);
	}

	if(m_jugador->m_saltar){
		saltar_jugador(_dt);
	}

	dibujar_balas_jugador();
	this->m_jugador->dibujar();
}

void TGestor::mover_jugador(glm::vec3 _dir){
	glm::vec3 _pos = m_jugador->m_posicion+_dir;
	/*
	if(m_mapa->m_cuarto_actual->colision_paredes(_pos)){
		m_jugador->mover(_pos);
	}*/
	m_jugador->mover(_pos);
}

void TGestor::crear_enemigos(unsigned _n){
	for(unsigned i=0; i<_n; i++){
		m_enemigos.push_back(new TEnemigo(RandomPosition(m_mapa->m_cuarto_dim.x,
														 -6, m_mapa->m_cuarto_dim.z)));
		// std::cout << *m_enemigos[i] << "\n";
	}
}

void TGestor::mover_enemigos(){
	glm::vec3 _pos;
	for(unsigned i=0; i<m_enemigos.size(); i++){
		_pos = m_enemigos[i]->m_posicion + m_enemigos[i]->m_direccion;
		if(m_mapa->m_cuarto_actual->colision_paredes(_pos)){
			m_enemigos[i]->mover(_pos);
		}
		else{
			m_enemigos[i]->m_direccion = RandomVect();
		}
	}
}

void TGestor::dibujar_enemigos(){
	mover_enemigos();
	for(unsigned i=0; i<m_enemigos.size(); i++){
		m_enemigos[i]->dibujar();
	}
}

TGestor::~TGestor(){
	
}