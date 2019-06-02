#include "../inc/mapa.h"
#include "../inc/tmanager.h"

#include <assert.h>
#include <FreeImage.h>

#include <iostream>

TMapa::TMapa(){
	//Inicializar cuartos

	this->m_cuarto_dim = glm::vec3(50,20,50);
	this->m_mundo_dim = glm::vec3(300,300,300);
	this->m_centro = glm::vec3(0.0f,-10.0f, 0.0f);

	//m_temp = (m_centro - m_mundo_dim)/2.0f;

	this->m_cuarto_actual = new TCuarto(m_centro, m_cuarto_dim);
	
	this->texturas_id[tfloor]  = TextureManager::Inst()->LoadTexture("data/texturas/floor.jpg",  GL_BGR_EXT, GL_RGB);
	this->texturas_id[twall]   = TextureManager::Inst()->LoadTexture("data/texturas/walld.jpg",  GL_BGR_EXT, GL_RGB, true);
	this->texturas_id[tpuerta] = TextureManager::Inst()->LoadTexture("data/texturas/puerta.jpg",  GL_BGR_EXT, GL_RGB);

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

	std::random_device rd;
    std::mt19937 rng(rd());
	generar_nivel_aleatorio(m_anchura, m_altura, m_num_cuartos, m_num_tesoros, m_cuartos, m_puertas, rng);

	m_vec_tcuartos = std::vector<TCuarto>(m_num_cuartos);
	glm::vec3 cuarto_centro = m_centro;
	int cont_cuartos = 0;
	int i_inicio, j_inicio;

	//buscar el cuarto inicial
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
	//crear el cuarto inicial y los anteriores al inicial
	//el cuarto inicial se inicializa con 'm_centro'
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
	//crear los cuartos siguientes al inicial
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

	//Inicializar puertas
	m_vec_tpuertas = std::vector<TPuerta>(m_puertas.size() * 2);
	ParCoord2D pc2d;
	auto it = m_puertas.begin();
	glm::vec3 centro_puerta;
	glm::vec2 dim_puerta(5, 15);
	int dx1, dy1, dx2, dy2;
	glm::vec2 centro1, centro2;
	Orientacion orient;
	
	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		pc2d = *it;
		++it;
		dx1 = pc2d.c1.x - j_inicio;
		dy1 = pc2d.c1.y - i_inicio;
		dx2 = pc2d.c2.x - j_inicio;
		dy2 = pc2d.c2.y - i_inicio;
		centro1 = glm::vec2(dx1 * m_cuarto_dim.x, dy1 * m_cuarto_dim.z);
		centro2 = glm::vec2(dx2 * m_cuarto_dim.x, dy2 * m_cuarto_dim.z);
		centro_puerta = glm::vec3((centro1.x + centro2.x)/2, -12.5, (centro1.y + centro2.y)/2);
		if (centro1.x - centro2.x == 0)
		{
			orient = x;
			centro_puerta.z += 0.0001;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, primero);
			++i;

			centro_puerta.z -= 0.0002;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, segundo);
		}
		else if (centro1.y - centro2.y == 0)
		{
			orient = z;
			centro_puerta.x += 0.0001;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, primero);
			++i;

			centro_puerta.x -= 0.0002;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, segundo);
		}
	}

	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		std::cout << m_vec_tpuertas[i].m_centro.x << " " << m_vec_tpuertas[i].m_centro.y << " " << m_vec_tpuertas[i].m_centro.z << "\n";
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
	for (int i = 0; i < m_vec_tcuartos.size(); ++i)
	{
		m_vec_tcuartos[i].dibujar(texturas_id);
	}	
	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		m_vec_tpuertas[i].dibujar(texturas_id);
	}
}

TMapa::~TMapa(){
// 	delete m_cuarto_actual;
}