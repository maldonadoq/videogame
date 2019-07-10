#ifndef _ITEM_H_
#define _ITEM_H_

#include "modelo.h"
#include "utils.h"

class TItem{
private:
    TModelo *m_modelo;
    int m_tipo;
public:
	int m_update;
	TModelo *m_inter;
    glm::vec3 m_posicion;
    TItem(glm::vec3, int, TModelo *);
    TItem(glm::vec3, int, int, TModelo *, TModelo *);

    void dibujar(bool);
    int colision(glm::vec3);
    ~TItem();
};

#endif