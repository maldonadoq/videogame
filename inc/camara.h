#ifndef _CAMARA_H_
#define _CAMARA_H_

#include <glm/glm.hpp>

class TCamara{
private:
public:	
	glm::vec4 m_perspective;	// fovy,ratio,znear,zfar
	glm::vec3 m_posicion;		// x,y,z
	glm::vec3 m_direccion;
	bool m_up;

	float m_angulo;
	float m_delta_mangle;
	float m_delta_tangle;

	TCamara(float _fovy, float _ratio,
		float _znear, float _zfar){
		this->m_perspective = glm::vec4(_fovy, _ratio, _znear, _zfar);
		this->m_posicion = glm::vec3(0,0,5);
		this->m_direccion = glm::vec3(0,0,-1);
		this->m_up = false;

		this->m_angulo = 0.0f;
		this->m_delta_tangle = 0.0f;	// tecla
		this->m_delta_mangle = 0.0f;	// mouse
	}

	void set_posicion(glm::vec3 _pos){
		this->m_posicion = _pos;
	}

	TCamara(){
		this->m_perspective = glm::vec4(0,0,0,0);
		this->m_posicion = glm::vec3(0,0,0);
		this->m_direccion = glm::vec3(0,0,0);
	}

	void actualizar(float _dt){
		if(m_delta_tangle){
			m_direccion.x = sin(m_angulo += (m_delta_tangle*_dt));
			m_direccion.z = -cos(m_angulo += (m_delta_tangle*_dt));
		}
	}

	~TCamara(){	};
};

#endif