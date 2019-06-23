#ifndef _MONSTRUO_H_
#define _MONSTRUO_H_

#include <iostream>
#include "enemigo.h"
#include "random.h"

class TMonstruo: public TEnemigo{
public:
    TMonstruo();
    TMonstruo(glm::vec3, TModelo *);
    ~TMonstruo(){};

    void mover(glm::vec3, glm::vec3, glm::vec3, float);
    void dibujar(glm::vec3, glm::vec3, bool);
    void disparar(glm::vec3, float);
    float get_size(float);
};

#endif