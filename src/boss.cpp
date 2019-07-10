#include "../inc/boss.h"

TBoss::TBoss(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = eboss;
    this->m_direccion = 10.0f*RandomVect();
    this->m_modelo = _model;
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion += (m_modelo->m_dim/2.0f);

    this->m_color = glm::vec3(0.0f,0.0f,1.0f);
}

void TBoss::mover(glm::vec3 _jug, glm::vec3 _dim, glm::vec3 _centro, float _dt){
    m_direccion = glm::normalize((_jug - glm::vec3(m_posicion.x, _jug.y, m_posicion.z)));
    glm::vec3 _pos = m_posicion + (m_direccion*_dt*5.0f);

    if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
        m_posicion = _pos;
        disparar(_jug, _dt);
    }
}

/*
    Verificar la colision del enemigo contra alguien
*/
int TBoss::colision(glm::vec3 _pos, float _r){
    int ty = -1;

    float dis = glm::distance(_pos, m_posicion);

    if(dis < (m_modelo->m_dim/2.0f + _r)){
        ty = 1;
        m_vida--;

        if(m_vida <= 0){
            ty = 4;
        }
    }

    return ty;
}

void TBoss::disparar(glm::vec3 _pos, float _dt){
	if(m_tiempo_disparar > 1.5f){
        glm::vec3 _dir = glm::normalize(_pos - m_posicion)*_dt*50.0f;
		TBala tb = {0.15f, m_posicion, _dir};

		m_balas.push_back(tb);
		m_tiempo_disparar = 0.0f;
	}
}

float TBoss::get_size(float _size){
    return (_size/(float)eboss)*m_vida;
}