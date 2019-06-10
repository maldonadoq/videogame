#include "../inc/puerta.h"

TPuerta::TPuerta()
{
    m_centro = glm::vec3(0, 0, 0);
    m_dim = glm::vec2(5, 15);
    m_orient = x;
    m_lado = primero;
}

TPuerta::TPuerta(glm::vec3 _centro, glm::vec2 _dim, Orientacion _orient, Lado _lado)
{
    this->m_centro = _centro;
    this->m_dim = _dim;
    this->m_orient = _orient;
    this->m_lado = _lado;
}

void TPuerta::dibujar(int _tid)
{
    glBindTexture(GL_TEXTURE_2D, _tid);

    glBegin(GL_QUADS);
        if (m_lado == primero)
        {
            if (m_orient == x)
            {
                glNormal3f(0, 0, 1);
            }
            else if (m_orient == z)
            {
                glNormal3f(1, 0, 0);
            }
        }
        else if (m_lado == segundo)
        {
            if (m_orient == x)
            {
                glNormal3f(0, 0, -1);
            }
            else if (m_orient == z)
            {
                glNormal3f(-1, 0, 0);
            }   
        }

        if (m_orient == x)
        {
            if (m_lado == primero)
            {
                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);
            
                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);
            
                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);
            }
            else
            {
                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y - m_dim.y/2, m_centro.z);

                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x - m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);

                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x + m_dim.x/2, m_centro.y + m_dim.y/2, m_centro.z);
            }
            
            
        }
        else if (m_orient == z)
        {
            if (m_lado == segundo)
            {
                glTexCoord2f(0, 1);
                glVertex3f(m_centro.x, m_centro.y + m_dim.y/2, m_centro.z + m_dim.x/2);
            
                glTexCoord2f(1, 1);
                glVertex3f(m_centro.x, m_centro.y + m_dim.y/2, m_centro.z - m_dim.x/2);

                glTexCoord2f(1, 0);
                glVertex3f(m_centro.x, m_centro.y - m_dim.y/2, m_centro.z - m_dim.x/2);

                glTexCoord2f(0, 0);
                glVertex3f(m_centro.x, m_centro.y - m_dim.y/2, m_centro.z + m_dim.x/2);
            }
            else
            {
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
}