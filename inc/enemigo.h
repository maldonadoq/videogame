#ifndef _ENEMIGO_H_
#define _ENEMIGO_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include "bala.h"
#include "persona.h"
#include "random.h"

class TEnemigo: public TPersona{
private:
  float m_tiempo_disparar;
public:	
    TEnemigo(glm::vec3);
    TEnemigo();
    ~TEnemigo();

	void mover(glm::vec3);
	void anhadir_bala(TBala);

	void dibujar();
	void set_posicion_inicial();
	glm::vec3 get_posicion();
	void disparar(float, glm::vec3);
};

#endif