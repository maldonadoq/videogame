#include "../inc/gestor.h"

TGestor::TGestor(){
	this->m_jugador = NULL;
	this->m_mapa = NULL;
	this->m_aceleracion = glm::vec3(0.0f, -9.81f, 0.0f);

	m_modelos.push_back(TModelo::get_modelo("pikachu"));
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

void TGestor::saltar_jugador(){
	if(m_jugador->m_saltar){
		m_jugador->m_time += m_dt;

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

void TGestor::dibujar_jugador(glm::vec3 _dir){
	if(m_jugador->m_mover){
		mover_jugador(m_dt*_dir*m_jugador->m_mover);
	}

	if(m_jugador->m_saltar){
		saltar_jugador();
	}

	dibujar_balas_jugador();
	this->m_jugador->dibujar();
}

void TGestor::mover_jugador(glm::vec3 _dir){
	glm::vec3 _pos = m_jugador->m_posicion+_dir;
	if(m_mapa->m_cuarto_actual->colision_paredes(_pos)){
		m_jugador->mover(_pos);
	}
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
		_pos = m_enemigos[i]->m_posicion + (m_enemigos[i]->m_direccion*m_dt);
		if(m_mapa->m_cuarto_actual->colision_paredes(_pos)){
			m_enemigos[i]->mover(_pos);
		}
		else{
			m_enemigos[i]->m_direccion = 10.0f*RandomVect();
		}
	}
}

void TGestor::dibujar_enemigos(){
	mover_enemigos();
	for(unsigned i=0; i<m_enemigos.size(); i++){
		m_enemigos[i]->dibujar();
		/*
		glPushMatrix();
			glTranslatef(m_enemigos[i]->m_posicion.x, m_enemigos[i]->m_posicion.y, m_enemigos[i]->m_posicion.z);

			glColor3f(0.7f, 0.7f, 0.2f);
	        glMaterialfv(GL_FRONT,GL_AMBIENT, glm::value_ptr(m_enemigos[i]->m_material.m_ambient));
	        glMaterialfv(GL_FRONT,GL_DIFFUSE, glm::value_ptr(m_enemigos[i]->m_material.m_diffuse));

	        glScalef(.35f, .35f, .35f);
	        // glRotatef(angle * 57.2957f, 0, 1, 0);
	        // glRotated(90, 1, 0, 0);
	        m_modelos[m_random[i]]->dibujar();
	    glPopMatrix();
	    */
	}
}

void TGestor::set_dt(float _dt){
	this->m_dt = _dt;
}

TGestor::~TGestor(){
	m_mapa = NULL;
	m_jugador = NULL;
	m_enemigos.clear();
	m_modelos.clear();
}