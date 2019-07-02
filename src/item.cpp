#include "../inc/item.h"

float ino_emit[]    = {1.0, 1.0, 1.0, 1.0};

TItem::TItem(glm::vec3 _pos, int _tipo, TModelo *_modelo){
    this->m_modelo = _modelo;
    this->m_posicion = _pos;
    this->m_posicion.y += m_modelo->m_dim/2.0f;
    this->m_tipo = _tipo;
}

void TItem::dibujar(bool _col){
    glPushMatrix();
        glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);

        if(_col){
            float emit[]    = {1.0, 0.0, 0.0, 1.0};
    		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
    			glColor3f(1,0,0);
    			glutWireSphere(m_modelo->m_dim/2.0f, 8, 8);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ino_emit);
        }

        m_modelo->dibujar();
    glPopMatrix();
}

int TItem::colision(glm::vec3 _pos){

    if(glm::distance(_pos, m_posicion) < m_modelo->m_dim/2.0f){
        return m_tipo;
    }

    return -1;
}

TItem::~TItem(){

}