#include "../inc/mapa.h"

#include <assert.h>
#include <FreeImage.h>
#include "../inc/tmanager.h"
#include <iostream>

TMapa::TMapa(){
	this->m_cuarto_dim = glm::vec3(50,20,50);
	this->m_mundo_dim = glm::vec3(300,300,300);
	this->m_centro = glm::vec3(0.0f,-10.0f, 0.0f);

	m_temp = (m_centro - m_mundo_dim)/2.0f;

	this->m_cuarto_actual = new TCuarto(m_centro, m_cuarto_dim);
	
	this->texturas_id[tfloor] = TextureManager::Inst()->LoadTexture("data/texturas/floor.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[twall]  = TextureManager::Inst()->LoadTexture("data/texturas/walld.jpg",  GL_BGR_EXT, GL_RGB, true);
	// this->texturas_id[twall]  = TextureManager::Inst()->LoadTexture("data/texturas/walld.jpg",  GL_BGR_EXT, GL_RGB);

	this->texturas_id[tfront] = TextureManager::Inst()->LoadTexture("data/sky/four/front.jpg", GL_BGR_EXT, GL_RGB);
	this->texturas_id[tback]  = TextureManager::Inst()->LoadTexture("data/sky/four/back.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[tleft]  = TextureManager::Inst()->LoadTexture("data/sky/four/left.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[tright] = TextureManager::Inst()->LoadTexture("data/sky/four/right.jpg", GL_BGR_EXT, GL_RGB);
	this->texturas_id[tup]    = TextureManager::Inst()->LoadTexture("data/sky/four/up.jpg",    GL_BGR_EXT, GL_RGB);
	this->texturas_id[tdown]  = TextureManager::Inst()->LoadTexture("data/sky/four/down.jpg",  GL_BGR_EXT, GL_RGB);

	/*
	this->texturas_id[tfront] = TextureManager::Inst()->LoadTexture("data/sky/three/front.png", GL_BGR_EXT, GL_RGB);
	this->texturas_id[tback]  = TextureManager::Inst()->LoadTexture("data/sky/three/back.png",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[tleft]  = TextureManager::Inst()->LoadTexture("data/sky/three/left.png",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[tright] = TextureManager::Inst()->LoadTexture("data/sky/three/right.png", GL_BGR_EXT, GL_RGB);
	this->texturas_id[tup]    = TextureManager::Inst()->LoadTexture("data/sky/three/up.png",    GL_BGR_EXT, GL_RGB);
	this->texturas_id[tdown]  = TextureManager::Inst()->LoadTexture("data/sky/three/down.png",  GL_BGR_EXT, GL_RGB);
	*/

	// this->texturas_id[0] = TextureManager::Inst()->LoadTexture("data/granito.jpg", GL_BGR_EXT, GL_RGB);
	// this->texturas_id[1] = TextureManager::Inst()->LoadTexture("data/brickt.jpg", GL_BGR_EXT, GL_RGB);
	// std::cout << texturas_id[0]	<< "\n";
}

void TMapa::dibujar_mundo(){
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, texturas_id[tfront]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y, m_temp.z+m_mundo_dim.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z+m_mundo_dim.z);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, texturas_id[tback]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, texturas_id[tleft]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, texturas_id[tright]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y,	m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y,	m_temp.z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, texturas_id[tup]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z+m_mundo_dim.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, texturas_id[tdown]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TMapa::dibujar(){
	dibujar_mundo();

	assert(m_cuarto_actual != NULL);
	this->m_cuarto_actual->dibujar(texturas_id);	
}

TMapa::~TMapa(){
// 	delete m_cuarto_actual;
}