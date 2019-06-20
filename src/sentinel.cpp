#include "../inc/sentinel.h"

int segm = 12;

TSentinel::TSentinel(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = 5;
    this->m_direccion = 10.0f*RandomVect();
    this->m_modelo = _model;
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion += (m_modelo->m_dim/2.0f);
}

void TSentinel::mover(glm::vec3 _jug, glm::vec3 _dim, glm::vec3 _centro, float _dt){
    disparar(_jug, _dt);
}

void TSentinel::disparar(glm::vec3 _pos, float _dt){
    if(m_tiempo_disparar > 5.0f){
        float x, z, theta;    		
        glm::vec3 tmp;
        tmp.y = 0;
		for(int i = 0; i < segm; i++){
		    theta = (float)(2*PI*i)/segm;
		    tmp.x = cos(theta);
		    tmp.z = sin(theta);

		    TBala tb = {0.2f, m_posicion, tmp*_dt*10.0f};
            m_balas.push_back(tb);
		}

		m_tiempo_disparar = 0.0f;
	}
}