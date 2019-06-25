#include "../inc/jugador.h"

TJugador::TJugador(){

}

TJugador::TJugador(glm::vec3 _pos){
	this->m_posicion = _pos;
	this->m_vida = 5;
	this->m_piso = m_posicion.y;
	this->m_dim = 5;
	this->m_mover = 0.0f;
	this->m_arma = asimple;
	// this->m_arma = arebote;
}

TJugador::~TJugador(){
	
}

void TJugador::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TJugador::dibujar(){
	if(m_camara->m_person){

		glm::vec2 a(m_camara->m_direccion.x, m_camara->m_direccion.z);
		glm::vec2 b(m_modelo->m_dir.x, m_modelo->m_dir.z);
		float angley = glm::orientedAngle(a, b)*180/PI;
		glPushMatrix();
			glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
			glRotatef(angley, 0.0f, 1.0f, 0.0f);
			m_modelo->dibujar();
		glPopMatrix();
	}
}

void TJugador::set_modelo(TModelo *_model){
	this->m_modelo = _model;
	this->m_posicion.y += m_modelo->m_dim/2.0f;
}

void TJugador::set_camara(TCamara *_camara){
	this->m_camara = _camara;
}

glm::vec3 TJugador::get_posicion(){
	return this->m_posicion;
}

void TJugador::disparar(glm::vec3 _dir, float _dt){
	switch (m_arma){
		case asimple:{
			m_balas.push_back(new TBala(0.2f, m_posicion+(m_camara->m_direccion*3.0f), m_camara->m_direccion*_dt*50.0f));
			break;
		}
		case adoble:{
			m_balas.push_back(new TBala(0.2f, m_posicion+(m_camara->m_direccion*10.0f), m_camara->m_direccion*_dt*60.0f));
			m_balas.push_back(new TBala(0.2f, m_posicion+(m_camara->m_direccion), m_camara->m_direccion*_dt*60.0f));
			break;
		}
		case areloj:{
			float x, z, theta;    		
	        glm::vec3 tmp;
	        tmp.y = 0;
			for(int i = 0; i < 12; i++){
			    theta = (float)(2*PI*i)/12;
			    tmp.x = cos(theta);
			    tmp.z = sin(theta);

	            m_balas.push_back(new TBala(0.2f, m_posicion, tmp*_dt*60.0f));
			}
			break;
		}
		case arebote:{
			m_balas.push_back(new TReal(0.2f, m_posicion+(m_camara->m_direccion*10.0f), m_camara->m_direccion*_dt*20.0f));
			break;
		}
		default:
			break;
	}
}