#include "../inc/mapa.h"
#include "../inc/tmanager.h"
#include "../inc/puerta_salida.h"

#include <assert.h>
#include <FreeImage.h>

#include <iostream>


glm::vec3 m_temp;

TMapa::TMapa(){

	//Inicializar cuartos
	this->m_cuarto_dim = glm::vec3(200,20,200);
	this->m_centro = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_mundo_dim = glm::vec3(4000,4000,4000);

	m_temp = (m_centro - m_mundo_dim)/2.0f;

	cuarto_texturas = vector<pair<int, int> >(12);
	cuarto_texturas[0].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor1.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[0].second = TextureManager::Inst()->LoadTexture("data/texturas/wall1.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[1].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor2.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[1].second = TextureManager::Inst()->LoadTexture("data/texturas/wall2.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[2].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor3.png",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[2].second = TextureManager::Inst()->LoadTexture("data/texturas/wall3.png",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[3].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor4.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[3].second = TextureManager::Inst()->LoadTexture("data/texturas/wall4.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[4].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor5.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[4].second = TextureManager::Inst()->LoadTexture("data/texturas/wall5.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[5].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor6.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[5].second = TextureManager::Inst()->LoadTexture("data/texturas/wall6.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[6].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor7.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[6].second = TextureManager::Inst()->LoadTexture("data/texturas/wall7.png",  GL_BGR_EXT, GL_RGB, true);

	cuarto_texturas[7].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor8.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[7].second = TextureManager::Inst()->LoadTexture("data/texturas/wall8.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[8].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor9.png",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[8].second = TextureManager::Inst()->LoadTexture("data/texturas/wall9.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[9].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor10.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[9].second = TextureManager::Inst()->LoadTexture("data/texturas/wall10.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[10].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor11.jpg",  GL_BGRA_EXT, GL_RGBA);
	cuarto_texturas[10].second = TextureManager::Inst()->LoadTexture("data/texturas/wall11.jpg",  GL_BGR_EXT, GL_RGB, true);
	cuarto_texturas[11].first  = TextureManager::Inst()->LoadTexture("data/texturas/floor12.jpg",  GL_BGR_EXT, GL_RGB);
	cuarto_texturas[11].second = TextureManager::Inst()->LoadTexture("data/texturas/wall12.jpg",  GL_BGR_EXT, GL_RGB, true);

	sky_texturas = vector<vector<int> >(m_num_niveles, vector<int>(6));
	sky_texturas[0][0] = TextureManager::Inst()->LoadTexture("data/sky/1/front.tga", GL_BGR_EXT, GL_RGB);
	sky_texturas[0][1] = TextureManager::Inst()->LoadTexture("data/sky/1/back.tga",  GL_BGR_EXT, GL_RGB);
	sky_texturas[0][2] = TextureManager::Inst()->LoadTexture("data/sky/1/left.tga",  GL_BGR_EXT, GL_RGB);
	sky_texturas[0][3] = TextureManager::Inst()->LoadTexture("data/sky/1/right.tga", GL_BGR_EXT, GL_RGB);
	sky_texturas[0][4] = TextureManager::Inst()->LoadTexture("data/sky/1/up.tga",    GL_BGR_EXT, GL_RGB);
	sky_texturas[0][5] = TextureManager::Inst()->LoadTexture("data/sky/1/down.tga",  GL_BGR_EXT, GL_RGB);

	sky_texturas[1][0] = TextureManager::Inst()->LoadTexture("data/sky/2/front.tga", GL_BGR_EXT, GL_RGB);
	sky_texturas[1][1] = TextureManager::Inst()->LoadTexture("data/sky/2/back.tga",  GL_BGR_EXT, GL_RGB);
	sky_texturas[1][2] = TextureManager::Inst()->LoadTexture("data/sky/2/left.tga",  GL_BGR_EXT, GL_RGB);
	sky_texturas[1][3] = TextureManager::Inst()->LoadTexture("data/sky/2/right.tga", GL_BGR_EXT, GL_RGB);
	sky_texturas[1][4] = TextureManager::Inst()->LoadTexture("data/sky/2/up.tga",    GL_BGR_EXT, GL_RGB);
	sky_texturas[1][5] = TextureManager::Inst()->LoadTexture("data/sky/2/down.tga",  GL_BGR_EXT, GL_RGB);

	sky_texturas[2][0] = TextureManager::Inst()->LoadTexture("data/sky/3/front.tga", GL_BGR_EXT, GL_RGB);
	sky_texturas[2][1] = TextureManager::Inst()->LoadTexture("data/sky/3/back.tga",  GL_BGR_EXT, GL_RGB);
	sky_texturas[2][2] = TextureManager::Inst()->LoadTexture("data/sky/3/left.tga",  GL_BGR_EXT, GL_RGB);
	sky_texturas[2][3] = TextureManager::Inst()->LoadTexture("data/sky/3/right.tga", GL_BGR_EXT, GL_RGB);
	sky_texturas[2][4] = TextureManager::Inst()->LoadTexture("data/sky/3/up.tga",    GL_BGR_EXT, GL_RGB);
	sky_texturas[2][5] = TextureManager::Inst()->LoadTexture("data/sky/3/down.tga",  GL_BGR_EXT, GL_RGB);
	
	puerta_textura = TextureManager::Inst()->LoadTexture("data/texturas/puerta1.jpg",  GL_BGR_EXT, GL_RGB);

	crear_mapa();
	this->nivel = 0;
}

void TMapa::new_level(){
	nivel = (nivel+1)%m_num_niveles;
}

void TMapa::crear_mapa(){
	std::random_device rd;
    std::mt19937 rng(rd());
	//std::mt19937 rng(0);
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


	std::vector<std::vector<TCuarto *> > tcuartos(m_cuartos.size(), std::vector<TCuarto *>(m_cuartos[0].size(), nullptr));

	int i = i_inicio;
	int j = j_inicio;
	std::string tipo;

	//crear el cuarto inicial y los anteriores al inicial
	//el cuarto inicial se inicializa con 'm_centro'
	for ( ; i >= 0; --i)
	{
		for ( ; j >= 0; --j)
		{
			if (m_cuartos[i][j] != 0)
			{
				if (m_cuartos[i][j] == 1)
				{
					tipo = "Normal";
				}
				else if (m_cuartos[i][j] == 2)
				{
					tipo = "Tesoro";
				}
				else if (m_cuartos[i][j] == 3)
				{
					tipo = "Llave Dorada";
				}
				else if (m_cuartos[i][j] == 4)
				{
					tipo = "Entrada";
				}
				else if (m_cuartos[i][j] == 5)
				{
					tipo = "Salida";
				}
				m_vec_tcuartos[cont_cuartos] = TCuarto(cuarto_centro, m_cuarto_dim, tipo);
				tcuartos[i][j] = &m_vec_tcuartos[cont_cuartos];
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
				if (m_cuartos[i][j] == 1)
				{
					tipo = "Normal";
				}
				else if (m_cuartos[i][j] == 2)
				{
					tipo = "Tesoro";
				}
				else if (m_cuartos[i][j] == 3)
				{
					tipo = "Llave Dorada";
				}
				else if (m_cuartos[i][j] == 4)
				{
					tipo = "Entrada";
				}
				else if (m_cuartos[i][j] == 5)
				{
					tipo = "Salida";
				}
				m_vec_tcuartos[cont_cuartos] = TCuarto(cuarto_centro, m_cuarto_dim, tipo);
				tcuartos[i][j] = &m_vec_tcuartos[cont_cuartos];
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
	m_vec_tpuertas = std::vector<TPuerta>(m_puertas.size());
	ParCoord2D pc2d;
	auto it = m_puertas.begin();
	glm::vec3 centro_puerta;
	glm::vec2 dim_puerta(10, 15);
	int dx1, dy1, dx2, dy2;
	glm::vec2 centro1, centro2;
	Orientacion orient;
	TCuarto* cuarto1;
	TCuarto* cuarto2;
	glm::vec3 centro_puerta_salida;

	
	for (int i = 0; i < m_vec_tpuertas.size(); ++i){
		pc2d = *it;
		++it;

		cuarto1 = tcuartos[pc2d.c1.y][pc2d.c1.x];
		cuarto2 = tcuartos[pc2d.c2.y][pc2d.c2.x];
		
		dx1 = pc2d.c1.x - j_inicio;
		dy1 = pc2d.c1.y - i_inicio;
		dx2 = pc2d.c2.x - j_inicio;
		dy2 = pc2d.c2.y - i_inicio;
		centro1 = glm::vec2(dx1 * m_cuarto_dim.x, dy1 * m_cuarto_dim.z);
		centro2 = glm::vec2(dx2 * m_cuarto_dim.x, dy2 * m_cuarto_dim.z);
		centro_puerta = glm::vec3((centro1.x + centro2.x)/2, dim_puerta.y/2.0f, (centro1.y + centro2.y)/2);
		if (centro1.x - centro2.x == 0){
			orient = x;
			if (cuarto1->m_tipo == "Salida"){
				if (centro1.y < centro2.y){
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.z -= this->m_cuarto_dim.z;
				}
				else{
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.z += this->m_cuarto_dim.z;
				}
				this->m_puerta_salida = new TPuertaSalida(centro_puerta_salida, dim_puerta, orient, cuarto1);
				cuarto1->m_puerta_salida = this->m_puerta_salida;
			}
			else if (cuarto2->m_tipo == "Salida"){
				if (centro1.y < centro2.y){
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.z += this->m_cuarto_dim.z;
				}
				else{
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.z -= this->m_cuarto_dim.z;
				}
				this->m_puerta_salida = new TPuertaSalida(centro_puerta_salida, dim_puerta, orient, cuarto2);
				cuarto2->m_puerta_salida = this->m_puerta_salida;
			}
		}
		else if (centro1.y - centro2.y == 0){
			orient = z;
			if (cuarto1->m_tipo == "Salida"){
				if (centro1.x < centro2.x){
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.x -= this->m_cuarto_dim.x;
				}
				else{
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.x += this->m_cuarto_dim.x;
				}
				this->m_puerta_salida = new TPuertaSalida(centro_puerta_salida, dim_puerta, orient, cuarto1);
				cuarto1->m_puerta_salida = this->m_puerta_salida;
			}
			else if (cuarto2->m_tipo == "Salida"){
				if (centro1.x < centro2.x){
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.x += this->m_cuarto_dim.x;
				}
				else{
					centro_puerta_salida = centro_puerta;
					centro_puerta_salida.x -= this->m_cuarto_dim.x;
				}
				this->m_puerta_salida = new TPuertaSalida(centro_puerta_salida, dim_puerta, orient, cuarto2);
				cuarto2->m_puerta_salida = this->m_puerta_salida;
			}
		}
		m_vec_tpuertas[i] = TPuerta(centro_puerta, dim_puerta, orient, cuarto1, cuarto2);

		cuarto1->m_puertas.push_back(&m_vec_tpuertas[i]);
		cuarto2->m_puertas.push_back(&m_vec_tpuertas[i]);
	}


	/*
	std::cout << "Coordenadas de los centros de las puertas:\n";
	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		std::cout << i+1 << ": " << m_vec_tpuertas[i].m_centro.x << " " << m_vec_tpuertas[i].m_centro.y << " " << m_vec_tpuertas[i].m_centro.z << "\n";
	}*/
}

void TMapa::dibujar(float _dt){
	dibujar_mundo();

	//assert(m_cuarto_actual != NULL);
	//this->m_cuarto_actual->dibujar(sky_texturas);
	int nt;
	for (int i = 0; i < m_vec_tcuartos.size(); ++i){
		nt = i%cuarto_texturas.size();
		m_vec_tcuartos[i].dibujar(cuarto_texturas[nt].first, cuarto_texturas[nt].second, _dt);
	}	
	for (int i = 0; i < m_vec_tpuertas.size(); ++i)
	{
		m_vec_tpuertas[i].dibujar(puerta_textura);
	}
	m_puerta_salida->dibujar(puerta_textura);
}

void TMapa::dibujar_mundo(){
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, sky_texturas[nivel][0]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y, m_temp.z+m_mundo_dim.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z+m_mundo_dim.z);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, sky_texturas[nivel][1]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, sky_texturas[nivel][2]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, sky_texturas[nivel][3]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y,	m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y,	m_temp.z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, sky_texturas[nivel][4]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y+m_mundo_dim.y, m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z+m_mundo_dim.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x,		  m_temp.y+m_mundo_dim.y,	m_temp.z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, sky_texturas[nivel][5]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_temp.x,		  m_temp.y,		m_temp.z+m_mundo_dim.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z+m_mundo_dim.z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_temp.x+m_mundo_dim.x, m_temp.y,		m_temp.z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, -1);
}

TMapa::~TMapa(){
// 	delete m_cuarto_actual;
}