#include "../inc/item.h"

GLfloat ino_emit[] = {1.0, 1.0, 1.0, 1.0};

TItem::TItem(glm::vec3 _pos, TModelo *_modelo){
    this->m_modelo = _modelo;
    this->m_posicion = _pos;
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

TItem::~TItem(){

}