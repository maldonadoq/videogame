#ifndef _MONSTRUO_H_
#define _MONSTRUO_H_

#include <iostream>
#include "enemigo.h"
#include "random.h"

class TMonstruo: public TEnemigo{
public:
    TMonstruo();
    TMonstruo(glm::vec3);
    ~TMonstruo(){};

    glm::vec3 mover(glm::vec3, glm::vec3, float);
    void disparar(glm::vec3, float);
};

#endif