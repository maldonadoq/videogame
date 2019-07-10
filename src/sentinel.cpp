#include "../inc/sentinel.h"

TSentinel::TSentinel(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = esentinel;
    this->m_direccion = 10.0f*RandomVect();
    this->m_modelo = _model;
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion += (m_modelo->m_dim/2.0f);

    this->m_color = glm::vec3(1.0f,0.0f,0.0f);
}

void TSentinel::mover(glm::vec3 _jug, glm::vec3 _dim, glm::vec3 _centro, float _dt){
    disparar(_jug, _dt);
    m_direccion = glm::normalize((_jug - glm::vec3(m_posicion.x, _jug.y, m_posicion.z)));
    glm::vec3 _pos = m_posicion + (m_direccion*_dt*2.0f);

    if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
        m_posicion = _pos;
    }
}

void TSentinel::ndirecciones(int segm, float _vel){
    float x, z, theta;          
    glm::vec3 tmp;
    tmp.y = 0;
    for(int i = 0; i < segm; i++){
        theta = (float)(2*PI*i)/segm;
        tmp.x = cos(theta);
        tmp.z = sin(theta);

        TBala tb = {0.2f, m_posicion, tmp*_vel};
        m_balas.push_back(tb);
    }
}

void TSentinel::disparar(glm::vec3 _pos, float _dt){
    if(glm::distance(_pos, m_posicion) < 30.0f){
        if(m_tiempo_disparar > 0.5f){
            ndirecciones(30, _dt*40.0f);
            m_tiempo_disparar = 0.0f;
        }
    }
    else{
        if(m_tiempo_disparar > 5.0f){
            ndirecciones(12, _dt*20.0f);
            m_tiempo_disparar = 0.0f;
        }
    }
}

float TSentinel::get_size(float _size){
    return (_size/(float)esentinel)*m_vida;
}