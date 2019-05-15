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

void TGestor::set_enemigo(TEnemigo *_enemigo){
	this->m_enemigo= _enemigo;
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

void TGestor::dibujar_enemigo(glm::vec3 _dir,float _dt){
	if(m_enemigo->m_mover){
		mover_enemigo(_dir*m_enemigo->m_mover);
	}
}

void TGestor::mover_jugador(glm::vec3 _dir){
	glm::vec3 _pos = m_jugador->m_posicion+_dir;
	if(m_mapa->m_cuarto_actual->colision_paredes(_pos)){
		m_jugador->mover(_pos);
	}	
}

void TGestor::mover_enemigo(glm::vec3 _dir){
	glm::vec3 _pos = m_jugador->m_posicion+_dir;
	glColor3f(1.0f, 1.0f, 1.0f);

	//glTranslatef(0,-5,-20);//posición
	glTranslatef(m_jugador->m_posicion.x,m_jugador->m_posicion.y,m_jugador->m_posicion.z-50);
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

TGestor::~TGestor(){
	
}