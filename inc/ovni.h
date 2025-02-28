#ifndef _OVNI_H_
#define _OVNI_H_

#include <iostream>
#include "enemigo.h"
#include "random.h"

class TOvni: public TEnemigo{
public:
    TOvni();
    TOvni(glm::vec3, TModelo *);
    ~TOvni(){};

    void mover(glm::vec3, glm::vec3, glm::vec3, float);
    void disparar(glm::vec3, float);
    float get_size(float);
};

#endif