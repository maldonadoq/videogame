#ifndef _CAMARA_H_
#define _CAMARA_H_

#include <glm/glm.hpp>

class TCamara{
private:
public:	
	glm::vec4 m_perspective;	// fovy,ratio,znear,zfar
	glm::vec3 m_posicion;		// x,y,z

	TCamara(float _fovy, float _ratio,
		float _znear, float _zfar){
		this->m_perspective = glm::vec4(_fovy, _ratio, _znear, _zfar);
		this->m_posicion = glm::vec3(50,20,50);
	}

	void setPosicion(glm::vec3 _pos){
		this->m_posicion = _pos;
	}

	TCamara(){
		this->m_perspective = glm::vec4(0,0,0,0);
		this->m_posicion = glm::vec3(0,0,0);
	}

	~TCamara(){	};
};

#endif