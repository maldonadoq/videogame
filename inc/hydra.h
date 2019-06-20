#ifndef _HYDRA_H_
#define _HYDRA_H_

#include <iostream>
#include <vector>
#include "enemigo.h"
#include "random.h"

using std::vector;

struct Hydra{
    glm::vec3 m_pos;
    glm::vec3 m_dir;
    int m_vid;
};

class THydra: public TEnemigo{
private:
    vector<Hydra> m_thydra;
    TModelo m_tmodel;
    bool m_split;
public:
    THydra();
    THydra(glm::vec3, TModelo *);
    ~THydra(){};

    int  colision(glm::vec3, float);
    void mover(glm::vec3, glm::vec3, glm::vec3, float);
    void disparar(glm::vec3, float);
    void dibujar(glm::vec3, glm::vec3, bool);
    void set_tmodel();
};

#endif