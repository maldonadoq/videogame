#include "../inc/mapa.h"

#include <assert.h>
#include <FreeImage.h>
#include "../inc/tmanager.h"
#include <iostream>

TMapa::TMapa(){
	this->m_cuarto_actual = new TCuarto(glm::vec3(0,-15,0), glm::vec3(100,30,100));
	
	this->texturas_id[0] = TextureManager::Inst()->LoadTexture("data/texturas/floor.jpg", GL_BGR_EXT, GL_RGB);
	this->texturas_id[1] = TextureManager::Inst()->LoadTexture("data/texturas/walld.jpg", GL_BGR_EXT, GL_RGB);

	// this->texturas_id[0] = TextureManager::Inst()->LoadTexture("data/granito.jpg", GL_BGR_EXT, GL_RGB);
	// this->texturas_id[1] = TextureManager::Inst()->LoadTexture("data/brickt.jpg", GL_BGR_EXT, GL_RGB);
	// std::cout << texturas_id[0]	<< "\n";
}

void TMapa::dibujar(){
	assert(m_cuarto_actual != NULL);
	this->m_cuarto_actual->dibujar(texturas_id);
}

TMapa::~TMapa(){
	delete m_cuarto_actual;
}