#include "../inc/mapa.h"
#include "../inc/tmanager.h"

#include <assert.h>
#include <FreeImage.h>

#include <iostream>

TMapa::TMapa(){
	this->m_cuarto_dim = glm::vec3(100,20,100);
	this->m_mundo_dim = glm::vec3(300,300,300);
	this->m_centro = glm::vec3(0.0f,-10.0f, 0.0f);

	this->m_cuarto_actual = new TCuarto(m_centro, m_cuarto_dim);
	
	this->texturas_id[0] = TextureManager::Inst()->LoadTexture("data/texturas/floor1.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[1] = TextureManager::Inst()->LoadTexture("data/texturas/floor2.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[2] = TextureManager::Inst()->LoadTexture("data/texturas/floor3.png",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[3] = TextureManager::Inst()->LoadTexture("data/texturas/floor4.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[4] = TextureManager::Inst()->LoadTexture("data/texturas/floor5.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[5] = TextureManager::Inst()->LoadTexture("data/texturas/floor6.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[6] = TextureManager::Inst()->LoadTexture("data/texturas/floor7.jpg",  GL_BGR_EXT, GL_RGB);

	this->texturas_id[7]  = TextureManager::Inst()->LoadTexture("data/texturas/wall1.jpg",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[8]  = TextureManager::Inst()->LoadTexture("data/texturas/wall2.jpg",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[9]  = TextureManager::Inst()->LoadTexture("data/texturas/wall3.png",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[10]  = TextureManager::Inst()->LoadTexture("data/texturas/wall4.jpg",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[11]  = TextureManager::Inst()->LoadTexture("data/texturas/wall5.jpg",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[12]  = TextureManager::Inst()->LoadTexture("data/texturas/wall6.jpg",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[13]  = TextureManager::Inst()->LoadTexture("data/texturas/wall7.png",  GL_BGR_EXT, GL_RGB, true);

	std::random_device rd;
    std::mt19937 rng(rd());
	generar_nivel_aleatorio(m_anchura, m_altura, m_num_cuartos, m_num_tesoros, m_cuartos, m_puertas, rng);

	m_vec_tcuartos = std::vector<TCuarto>(m_num_cuartos);
	glm::vec3 cuarto_centro = m_centro;
	int cont_cuartos = 0;
	int i_inicio, j_inicio;
	for (i_inicio = 0 ; i_inicio < m_altura; ++i_inicio)
	{
		for (j_inicio = 0 ; j_inicio < m_anchura; ++j_inicio)
		{
			if (m_cuartos[i_inicio][j_inicio] == 4)
			{
				break;
			}
		}
		if (m_cuartos[i_inicio][j_inicio] == 4)
		{
			break;
		}
	}

	int i = i_inicio;
	int j = j_inicio;
	for ( ; i >= 0; --i)
	{
		for ( ; j >= 0; --j)
		{
			if (m_cuartos[i][j] != 0)
			{
				m_vec_tcuartos[cont_cuartos] = TCuarto(cuarto_centro, m_cuarto_dim);
				++cont_cuartos;
			}
			cuarto_centro.x -= m_cuarto_dim.x;
		}
		cuarto_centro.x = m_centro.x + ((m_anchura - 1) * m_cuarto_dim.x);
		cuarto_centro.z -= m_cuarto_dim.z;
		j = m_anchura - 1;
	}


	i = i_inicio;
	j = j_inicio + 1;
	cuarto_centro = m_centro;
	cuarto_centro.x += m_cuarto_dim.x;
	for ( ; i < m_altura; ++i)
	{
		for ( ; j < m_anchura; ++j)
		{
			if (m_cuartos[i][j] != 0)
			{
				m_vec_tcuartos[cont_cuartos] = TCuarto(cuarto_centro, m_cuarto_dim);
				++cont_cuartos;
			}
			cuarto_centro.x += m_cuarto_dim.x;
		}
		cuarto_centro.x = m_centro.x;
		cuarto_centro.z += m_cuarto_dim.z;
		j = 0;
	}
}

/*
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
}*/

void TMapa::dibujar_cuartos()
{

}

void TMapa::dibujar(){
	//dibujar_mundo();

	//assert(m_cuarto_actual != NULL);
	//this->m_cuarto_actual->dibujar(texturas_id);
	for (int i = 0; i < m_vec_tcuartos.size(); ++i){
		m_vec_tcuartos[i].dibujar(texturas_id[i], texturas_id[i+m_num_cuartos]);
	}	
}

TMapa::~TMapa(){
// 	delete m_cuarto_actual;
}