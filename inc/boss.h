#ifndef _BOSS_H_
#define _BOSS_H_

#include <iostream>
#include "enemigo.h"
#include "random.h"

class TBoss: public TEnemigo{
public:
    TBoss();
    TBoss(glm::vec3, TModelo *);
    ~TBoss(){};

    void mover(glm::vec3, glm::vec3, glm::vec3, float);
    void disparar(glm::vec3, float);
    int  colision(glm::vec3, float);
    float get_size(float);
};

#endif