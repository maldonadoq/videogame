#ifndef _ITEM_H_
#define _ITEM_H_

#include "modelo.h"

class TItem{
private:
    TModelo *m_modelo;
public:
    glm::vec3 m_posicion;
    int m_tipo;
    TItem(glm::vec3, TModelo *);

    void dibujar();
    ~TItem();
};

#endif