#ifndef _BALAS_H_
#define _BALAS_H_

#include <GL/glut.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp> 
#include "random.h"
#include "utils.h"

// Bala normal
class TBala{
public:
	float m_radio;
	glm::vec3 m_posicion;
	glm::vec3 m_direccion;

	TBala(float, glm::vec3, glm::vec3);
	TBala();

	virtual ~TBala(){}

	void dibujar();
	virtual bool paredes(glm::vec3, glm::vec3);
};

// Bala con rebote
class TReal: public TBala{
private:
	int m_rebotes;
public:
	TReal();
	TReal(float, glm::vec3, glm::vec3);

	bool paredes(glm::vec3, glm::vec3);
};

#endif