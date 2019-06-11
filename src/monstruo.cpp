#include "../inc/monstruo.h"

TMonstruo::TMonstruo(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = 5;
    this->m_direccion = 10.0f*RandomVect();
    this->m_modelo = _model;
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion += (m_modelo->m_dim/2.0f);
}

glm::vec3 TMonstruo::mover(glm::vec3 _dim, glm::vec3 _centro, float _dt){
    // std::cout << "monster moviendose\n";
    glm::vec3 _pos = m_posicion + (m_direccion*_dt);
    if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
        m_posicion = _pos;
    }
    else{
        restart();
    }
}

void TMonstruo::disparar(glm::vec3 _pos, float _dt){
	if(m_tiempo_disparar > 2.5f){
        // std::cout << "shoot!\n";
        glm::vec3 _dir = glm::normalize(_pos - m_posicion)*_dt*50.0f;
		TBala tb = {0.2f, m_posicion, _dir};

		m_balas.push_back(tb);
		m_tiempo_disparar = 0.0f;
	}
}