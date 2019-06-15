#ifndef _HYDRA_H_
#define _HYDRA_H_

#include <iostream>
#include "enemigo.h"
#include "random.h"

class THydra: public TEnemigo{
public:
    THydra();
    THydra(glm::vec3, TModelo *);
    ~THydra(){};

    void mover(glm::vec3, glm::vec3, float);
    void disparar(glm::vec3, float);
    void dibujar(glm::vec3, glm::vec3);
};

#endif