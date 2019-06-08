#include "../inc/mapa.h"
#include "../inc/tmanager.h"

#include <assert.h>
#include <FreeImage.h>

#include <iostream>

TMapa::TMapa(){

	//Inicializar cuartos
	this->m_cuarto_dim = glm::vec3(100,20,100);
	this->m_centro = glm::vec3(0.0f, 0.0f, 0.0f);

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

	this->texturas_id[14]  = TextureManager::Inst()->LoadTexture("data/texturas/puerta1.jpg",  GL_BGR_EXT, GL_RGB);


	std::random_device rd;
    std::mt19937 rng(rd());
	generar_nivel_aleatorio(m_anchura, m_altura, m_num_cuartos, m_num_tesoros, m_cuartos, m_puertas, rng);

	/*
	std::cout << "Cuartos generados:\n";
	imprimir_matriz_enteros(m_cuartos, m_anchura, m_altura);
    std::cout << "\n";*/

	m_vec_tcuartos = std::vector<TCuarto>(m_num_cuartos);
	glm::vec3 cuarto_centro = m_centro;
	int cont_cuartos = 0;
	int i_inicio, j_inicio;
	bool encontro_cuarto_inicial = false;

	//buscar el cuarto inicial
	for (i_inicio = 0 ; i_inicio < m_altura; ++i_inicio)
	{
		for (j_inicio = 0 ; j_inicio < m_anchura; ++j_inicio)
		{
			if (m_cuartos[i_inicio][j_inicio] == 4)
			{
				encontro_cuarto_inicial = true;
				break;
			}
		}
		if (encontro_cuarto_inicial == true)
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
		cuarto_centro.x = m_centro.x + (((m_anchura - 1) - j_inicio) * m_cuarto_dim.x);
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
		cuarto_centro.x = m_centro.x - (j_inicio * m_cuarto_dim.x);
		cuarto_centro.z += m_cuarto_dim.z;
		j = 0;
	}

	/*
	std::cout << "Coordenadas de los centros de los cuartos\n";
	for (int i = 0; i < m_vec_tcuartos.size(); ++i)
	{
		std::cout << i+1 << ": " << m_vec_tcuartos[i].m_centro.x;
		std::cout << ", " << m_vec_tcuartos[i].m_centro.z << "\n";
	}*/

	//Inicializar puertas
	m_vec_tpuertas = std::vector<TPuerta>(m_puertas.size() * 2);
	ParCoord2D pc2d;
	auto it = m_puertas.begin();
	glm::vec3 centro_puerta;
	glm::vec2 dim_puerta(10, 30);
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
			centro_puerta.z += 0.1;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, primero);
			++i;

			centro_puerta.z -= 0.2;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, segundo);
		}
		else if (centro1.y - centro2.y == 0)
		{
			orient = z;
			centro_puerta.x += 0.1;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, primero);
			++i;

			centro_puerta.x -= 0.2;
			m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, segundo);
		}
	}

	/*
	std::cout << "Coordenadas de los centros de las puertas:\n";
	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		std::cout << i+1 << ": " << m_vec_tpuertas[i].m_centro.x << " " << m_vec_tpuertas[i].m_centro.y << " " << m_vec_tpuertas[i].m_centro.z << "\n";
	}*/
}

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
	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		m_vec_tpuertas[i].dibujar(texturas_id);
	}
}

TMapa::~TMapa(){
// 	delete m_cuarto_actual;
}