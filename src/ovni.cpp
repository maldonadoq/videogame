#include "../inc/ovni.h"

TOvni::TOvni(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = eovni;
    this->m_modelo = _model;
    this->m_direccion = 10.0f*RandomVect();
    this->m_tiempo_disparar = 0.0f;

    this->m_color = glm::vec3(0.0f,1.0f,0.0f);
}

void TOvni::mover(glm::vec3 _jug, glm::vec3 _dim, glm::vec3 _centro, float _dt){
    // std::cout << "ovni moviendose\n";
    // revisar la colision
    glm::vec3 _pos = m_posicion + (m_direccion*_dt);
    if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
        m_posicion = _pos;
        disparar(_jug, _dt);
    }
    else{
        restart();
    }
}

void TOvni::disparar(glm::vec3 _pos, float _dt){
	if(m_tiempo_disparar > 2.5f){
        // std::cout << "shoot!\n";
        glm::vec3 _dir = glm::normalize(_pos - m_posicion)*_dt*50.0f;
		TBala tb = {0.2f, m_posicion, _dir};

		m_balas.push_back(tb);
		m_tiempo_disparar = 0.0f;
	}
}

float TOvni::get_size(float _size){
    return (_size/(float)eovni)*m_vida;
}