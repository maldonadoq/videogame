#ifndef _PERSONA_H_
#define _PERSONA_H_

#include <glm/glm.hpp>
#include <vector>
#include "bala.h"

class TPersona{
public:
    std::vector<TBala> m_balas;
	
	glm::vec3 m_posicion;	
	glm::vec3 m_dim;	

	glm::vec3 m_posicion_inicial;
	glm::vec3 m_velocidad_inicial;

	float m_piso;
	float m_time;

	float m_mover;
    int m_vida;
    bool m_saltar;
    
    TPersona(glm::vec3 _pos){
    	this->m_posicion = _pos;
		this->m_piso = m_posicion.y;
		this->m_time = 0.0f;
    }

    TPersona(){

    }

    ~TPersona(){};

	virtual void mover(glm::vec3) = 0;
	virtual void anhadir_bala(TBala) = 0;
	virtual void dibujar() = 0;
	virtual void set_posicion_inicial() = 0;
	virtual glm::vec3 get_posicion() = 0;
};

#endif