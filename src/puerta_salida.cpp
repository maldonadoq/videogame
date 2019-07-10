#include "../inc/puerta_salida.h"

TPuertaSalida::TPuertaSalida()
{
    m_centro = glm::vec3(0, 0, 0);
    m_dim = glm::vec2(5, 15);
    m_orient = x;
}

TPuertaSalida::TPuertaSalida(glm::vec3 _centro, glm::vec2 _dim, Orientacion _orient,
                 TCuarto* cuarto1)
{
    this->m_centro = _centro;
    this->m_dim = _dim;
    this->m_orient = _orient;
    this->m_cuarto1 = cuarto1;
}

void TPuertaSalida::dibujar(int _tid)
{
    glBindTexture(GL_TEXTURE_2D, _tid);

    //Primer lado de la puerta
    glm::vec3 centro_aux = this->m_centro;
    glBegin(GL_QUADS);
        if (m_orient == x){
            if (this->m_cuarto1->m_centro.z < this->m_centro.z){
                this->m_centro.z -= 0.5;
                glNormal3f(0, 0, -1);
                
                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);

                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);

                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);
            }
            else{
                this->m_centro.z += 0.5;
                glNormal3f(0, 0, 1);

                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);
            
                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);
            
                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);
            }
        }
        else if (m_orient == z){
            if (this->m_cuarto1->m_centro.x < this->m_centro.x){
                this->m_centro.x -= 0.5;
                glNormal3f(-1, 0, 0);

                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x, m_centro.y + m_dim.y/2, m_centro.z + m_dim.x/2);
            
                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x, m_centro.y + m_dim.y/2, m_centro.z - m_dim.x/2);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x, m_centro.y - m_dim.y/2, m_centro.z - m_dim.x/2);

                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x, m_centro.y - m_dim.y/2, m_centro.z + m_dim.x/2);
            }
            else{
                this->m_centro.x += 0.5;
                glNormal3f(1, 0, 0);
                
                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x, m_centro.y - m_dim.y/2, m_centro.z + m_dim.x/2);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x, m_centro.y - m_dim.y/2, m_centro.z - m_dim.x/2);

                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x, m_centro.y + m_dim.y/2, m_centro.z - m_dim.x/2);

                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x, m_centro.y + m_dim.y/2, m_centro.z + m_dim.x/2);
            }
        }
    glEnd();

    this->m_centro = centro_aux;

    glBindTexture(GL_TEXTURE_2D, 0);
}