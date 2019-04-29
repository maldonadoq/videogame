#include "../inc/cuarto.h"

TCuarto::TCuarto(){

}

TCuarto::TCuarto(glm::vec3 _centro, glm::vec3 m_dim){
	this->m_centro = _centro;
	this->m_dim = m_dim;
	// this->m_escala = glm::vec3((float)m_dim.x/10,(float)m_dim.y/10,(float)m_dim.z/10);
	this->m_escala = m_dim/10.0f;
}

TCuarto::~TCuarto(){
}

void TCuarto::dibujar_paredes(){
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		// z-y
		// glTexCoord2f(1.0f, 1.0f);
		glTexCoord2f(m_escala.z, m_escala.y);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y + m_dim.y, m_centro.z - m_dim.z);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y + m_dim.y, m_centro.z + m_dim.z);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y, m_centro.z + m_dim.z);
		
		glTexCoord2f(m_escala.z, 0.0f);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y, m_centro.z - m_dim.z);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		
		glTexCoord2f(m_escala.z, m_escala.y);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y + m_dim.y, m_centro.z + m_dim.z);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y + m_dim.y, m_centro.z - m_dim.z);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y, m_centro.z - m_dim.z);
		
		glTexCoord2f(m_escala.z, 0.0f);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y, m_centro.z + m_dim.z);				
	glEnd();

	// x-y
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		
		glTexCoord2f(m_escala.x, m_escala.y);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y + m_dim.y, m_centro.z -m_dim.z);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y + m_dim.y, m_centro.z -m_dim.z);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y, m_centro.z -m_dim.z);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y, m_centro.z -m_dim.z);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		
		glTexCoord2f(m_escala.x, m_escala.y);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y + m_dim.y, m_centro.z +m_dim.z);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y + m_dim.y, m_centro.z +m_dim.z);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y, m_centro.z +m_dim.z);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y, m_centro.z +m_dim.z);
	glEnd();
}

void TCuarto::dibujar_piso(){
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		// x-z
		glTexCoord2f(m_escala.x, m_escala.z);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y, m_centro.z + m_dim.z);
		
		glTexCoord2f(0.0f, m_escala.z);
		glVertex3f(m_centro.x + m_dim.x, m_centro.y, m_centro.z - m_dim.z);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y, m_centro.z - m_dim.z);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x - m_dim.x, m_centro.y, m_centro.z + m_dim.z);
	glEnd();
}

void TCuarto::dibujar(int *_tid){
	glBindTexture(GL_TEXTURE_2D, _tid[0]);
	dibujar_piso();	

	glBindTexture(GL_TEXTURE_2D, _tid[1]);
	dibujar_paredes();
}