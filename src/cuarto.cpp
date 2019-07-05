/*
Contiene toda la informacion relacionada con un cuarto,
como dibujarlo, las posiciones de las paredes y suelo, y
tambien una funcion para detectar colision del personaje con
el cuarto.
*/

#include "../inc/cuarto.h"

/*
	Constructor de la clase Cuarto
	centro: centro del cuarto
	dim: dimension del cuarto
	escala: cuantas veces se repite la textura en las paredes
	jugador: puntero hacia el jugador
	enemigos: vector de enemigos presente en el cuarto
	items: vector de items en el cuarto
	colision: mostrar una esfera vacia alrededor del objetos
*/
TCuarto::TCuarto(){
	this->m_centro = glm::vec3(0,0,0);
	this->m_dim = glm::vec3(10,5,10);
	this->m_escala = m_dim/5.0f;
	this->m_jugador = NULL;
	this->m_enemigos.clear();
	this->m_items.clear();

	this->m_colision = true;
}

TCuarto::TCuarto(glm::vec3 _centro, glm::vec3 m_dim, std::string tipo){
	this->m_centro = _centro;
	this->m_dim = m_dim;
	this->m_escala = m_dim/10.0f;
	this->m_jugador = NULL;
	this->m_enemigos.clear();
	this->m_items.clear();
	this->m_tipo = tipo; 

	this->m_colision = true;
}

/*
	Dibujar la paredes del cuarto
	Se toma en cuenta el centro y la dimensión del cuarto
	
	z
	-------------
	|			|
	|	centro	|dim
	|	  -     |
	|			|
	|			|
	------------- x
	Dim
*/
void TCuarto::dibujar_paredes(){

	float tx = m_dim.x/2;
	float tz = m_dim.z/2;

	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		// z-y
		// glTexCoord2f(1.0f, 1.0f);
		glTexCoord2f(m_escala.z, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z - tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z + tz);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z + tz);
		
		glTexCoord2f(m_escala.z, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z - tz);				
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		
		glTexCoord2f(m_escala.z, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z + tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z - tz);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z - tz);
		
		glTexCoord2f(m_escala.z, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z + tz);				
	glEnd();

	// x-y
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		
		glTexCoord2f(m_escala.x, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z -tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z -tz);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z -tz);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z -tz);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		
		glTexCoord2f(m_escala.x, m_escala.y);
		glVertex3f(m_centro.x - tx, m_centro.y + m_dim.y, m_centro.z +tz);
		
		glTexCoord2f(0.0f, m_escala.y);
		glVertex3f(m_centro.x + tx, m_centro.y + m_dim.y, m_centro.z +tz);		

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z +tz);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z +tz);
	glEnd();
}

/*
	Dibujar el piso del cuarto
	Similar a una pared en el cuarto
*/
void TCuarto::dibujar_piso(){
	float tx = m_dim.x/2;
	float tz = m_dim.z/2;
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		// x-z
		glTexCoord2f(m_escala.x, m_escala.z);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z + tz);
		
		glTexCoord2f(0.0f, m_escala.z);
		glVertex3f(m_centro.x + tx, m_centro.y, m_centro.z - tz);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z - tz);
		
		glTexCoord2f(m_escala.x, 0.0f);
		glVertex3f(m_centro.x - tx, m_centro.y, m_centro.z + tz);
	glEnd();
}

/*
	Metodo que llama a las funcion:
		dibujar_pared
		dibujar_piso
	Aplica la textura para cada tipo
	Si en el cuarto está el jugador, se dibujará los items y enemigos
*/
void TCuarto::dibujar(int _tf, int _tw, float _dt){
	glBindTexture(GL_TEXTURE_2D, _tf);
	dibujar_piso();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, _tw);
	dibujar_paredes();
	glBindTexture(GL_TEXTURE_2D, 0);


	if(m_jugador != nullptr){
		dibujar_enemigos(_dt);
		dibujar_items();
	}
}

/*
	Añadir un nuevo enemigo en el cuarto
	y actualizar su posición en dicho cuarto
*/
void TCuarto::set_enemigo(TEnemigo *_enemigo){
	glm::vec3 tmp = (m_dim/2.0f) - 10.0f;
	_enemigo->m_posicion += m_centro + RandomPosition(tmp.x, 0, tmp.z);
	this->m_enemigos.push_back(_enemigo);
}

/*
	Añadir un nuevo item en el cuarto
	y actualizar su posición en dicho cuarto
*/
void TCuarto::set_item(TItem *_item){
	glm::vec3 tmp = (m_dim/2.0f) - 5.0f;
	_item->m_posicion += m_centro + RandomPosition(tmp.x, 0, tmp.z);
	this->m_items.push_back(_item);
}

/*
	El jugador ingresa a dicho cuarto
*/
void TCuarto::set_jugador(TJugador *_jugador){
	assert(_jugador != NULL);
	_jugador->m_posicion += m_centro;
	this->m_jugador = _jugador;
}

/*
	Dibujar los items en el cuarto
*/
void TCuarto::dibujar_items(){
	int t, i;
	for(i=0; i<(int)m_items.size(); i++){
		m_items[i]->dibujar(m_colision);
		t = m_items[i]->colision(m_jugador->m_posicion);
		if(t >= 0){
			m_items.erase(m_items.begin() + i);
			i--;

			switch (t){
				case 0:{
					cout << "corazón con 4 vidas!\n";
					m_jugador->m_vida += 4;
					break;
				}
				case 1:{
					cout << "roca!\n";
					break;
				}
				case 2:{
					cout << "chest!\n";
					break;
				}
				case 3:{
					cout << "!arma doble obtenida\n";
					m_jugador->set_arma(1);
					break;
				}
				case 4:{
					cout << "arma que dispara en 12 direcciones!\n";
					m_jugador->set_arma(2);
					break;
				}
				case 5:{
					cout << "arma con balas que rebotan!\n";
					m_jugador->set_arma(3);
					break;
				}
				default:
					break;
			}
		}
	}
}

/*
	función que dibuja a los enemigos en el cuarto
		mueve a los enemigos (cada uno con su función de moverse propia)
		dibuja el modelo del jugador
		dibujar la barra de vida
		carga el arma, para disparar de nuevo
*/
void TCuarto::dibujar_enemigos(float _dt){
	for(unsigned i=0; i<m_enemigos.size(); i++){
		m_enemigos[i]->mover(m_jugador->m_posicion, m_dim, m_centro, _dt);

		m_enemigos[i]->dibujar_balas(m_dim, m_centro, m_jugador);
		m_enemigos[i]->dibujar(m_dim, m_centro, m_colision);
		
		m_enemigos[i]->barra_vida(m_jugador->m_posicion);
		m_enemigos[i]->cargar(_dt);
	}
}

bool TCuarto::verificar_puertas(TJugador* jugador, TCuarto** cuarto_actual){
	glm::vec3* pos_jug = &(jugador->m_posicion);
	glm::vec3 aux;
	bool t = false;
	for (auto it = this->m_puertas.begin(); it != this->m_puertas.end(); ++it){
		aux = (*it)->m_centro;
		aux.y = pos_jug->y;
		if (glm::distance(*pos_jug, aux) < 10.0f){  //estoy en area para entrar a otro cuarto
			(*cuarto_actual)->m_jugador = nullptr;

			if ((*it)->m_cuarto1 == *cuarto_actual){
				*cuarto_actual = (*it)->m_cuarto2;
				(*it)->m_cuarto2->m_jugador = jugador;

				if ((*it)->m_orient == x){
					*pos_jug = glm::vec3((*it)->m_centro.x, pos_jug->y, (*it)->m_centro.z);
					if ((*it)->m_cuarto1->m_centro.z < (*it)->m_cuarto2->m_centro.z){
						pos_jug->z += 10;
					}
					else
					{
						pos_jug->z -= 10;
					}
				}
				else{  //m_orient == z
					*pos_jug = glm::vec3((*it)->m_centro.x, pos_jug->y, (*it)->m_centro.z);
					if ((*it)->m_cuarto1->m_centro.x < (*it)->m_cuarto2->m_centro.x){
						pos_jug->x += 10;
					}
					else
					{
						pos_jug->x -= 10;
					}
				}
			}
			else{  //m_cuarto2 == *cuarto_actual
				*cuarto_actual = (*it)->m_cuarto1;
				(*it)->m_cuarto1->m_jugador = jugador;

				if ((*it)->m_orient == x){
					*pos_jug = glm::vec3((*it)->m_centro.x, pos_jug->y, (*it)->m_centro.z);
					if ((*it)->m_cuarto1->m_centro.z < (*it)->m_cuarto2->m_centro.z){
						pos_jug->z -= 10;
					}
					else
					{
						pos_jug->z += 10;
					}
				}
				else{  //m_orient == z
					*pos_jug = glm::vec3((*it)->m_centro.x, pos_jug->y, (*it)->m_centro.z);
					if ((*it)->m_cuarto1->m_centro.x < (*it)->m_cuarto2->m_centro.x){
						pos_jug->x -= 10;
					}
					else
					{
						pos_jug->x += 10;
					}
				}
			}

			t = true;
			break;
		}
	}

	return t;
}

TCuarto::~TCuarto(){

}