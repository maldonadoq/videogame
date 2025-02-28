#ifndef _SENTINEL_H_
#define _SENTINEL_H_

#include <iostream>
#include <vector>
#include "enemigo.h"
#include "random.h"

class TSentinel: public TEnemigo{
private:
	void ndirecciones(int, float);
public:
    TSentinel();
    TSentinel(glm::vec3, TModelo *);
    ~TSentinel(){};

    void mover(glm::vec3, glm::vec3, glm::vec3, float);
    void disparar(glm::vec3, float);
    float get_size(float);
};

#endif