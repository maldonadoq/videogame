/*
Contiene el codigo sobre un enemigo, su posicion,
su movimiento, asi como una funcion para dibujarlo
y disparar.
*/

#include "../inc/enemigo.h"

TEnemigo::TEnemigo(glm::vec3 _pos){
	this->m_posicion = _pos;
}

void TEnemigo::dibujar(glm::vec3 _dim, glm::vec3 _centro){
	dibujar_balas(_dim, _centro);
	glPushMatrix();
		glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
		glLineWidth(3);
		glColor3f(0.0f, 1.0f, 0.0f);

		glutWireSphere(m_modelo->m_dim, 8, 8);
		// glutSolidSphere(m_dim, 8, 8);

		// glScalef(0.2f, 0.2f, 0.2f);
		// glRotatef(-90, 1, 0, 0);
		m_modelo->dibujar();
	glPopMatrix();
}

void TEnemigo::anhadir_bala(TBala _bala){
	this->m_balas.push_back(_bala);
}

void TEnemigo::cargar(float _dt){
	m_tiempo_disparar += _dt;
}

void TEnemigo::dibujar_balas(glm::vec3 _dim, glm::vec3 _centro){
	int i;
	// std::cout << m_balas.size() << "| ";
	glColor3f(0.0f, 1.0f, 0.0f);
	for(i=0; i<(int)m_balas.size(); i++){
		glPushMatrix();
			glTranslatef(
				m_balas[i].m_posicion.x,
				m_balas[i].m_posicion.y,
				m_balas[i].m_posicion.z
			);

			glutSolidSphere(m_balas[i].m_radio,8,8);
		glPopMatrix();
		m_balas[i].m_posicion += m_balas[i].m_direccion;

		if(!cuarto_colision(_dim, _centro, m_balas[i].m_posicion)){
			m_balas.erase(m_balas.begin() + i);
			i--;
		}
	}
}

int TEnemigo::colision(glm::vec3 _pos, float _r){
	int ty = -1;

	float dis = glm::distance(_pos, m_posicion);
	//std::cout << dis << "," << (_r+m_dim) << "\t|";

	if(dis < (m_modelo->m_dim + _r)){
		ty = 1;
		m_vida--;

		if(m_vida <= 0){
			ty = 2;
		}
	}

	// std::cout << ty << " ";

	return ty;
}

void TEnemigo::barra_vida(){
	glPushMatrix();		
		glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
		glTranslatef(0.0f ,10.0f, 0.0f);
		//glutSolidSphere(1,20,20);
		//glutSolidCube(3);	

		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
			// Top face (y = 1.0f)
			// Define vertices in counter-clockwise (CCW) order with normal pointing out
			glColor3f(0.0f, 1.0f, 0.0f);     // Green
			glVertex3f( 1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f,  1.0f);
			glVertex3f( 1.0f, 1.0f,  1.0f);
		
			// Bottom face (y = -1.0f)
			glColor3f(1.0f, 0.5f, 0.0f);     // Orange
			glVertex3f( 1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f( 1.0f, -1.0f, -1.0f);
		
			// Front face  (z = 1.0f)
			glColor3f(1.0f, 0.0f, 0.0f);     // Red
			glVertex3f( 1.0f,  1.0f, 1.0f);
			glVertex3f(-1.0f,  1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f( 1.0f, -1.0f, 1.0f);
		
			// Back face (z = -1.0f)
			glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
			glVertex3f( 1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f( 1.0f,  1.0f, -1.0f);
		
			// Left face (x = -1.0f)
			glColor3f(0.0f, 0.0f, 1.0f);     // Blue
			glVertex3f(-1.0f,  1.0f,  1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
		
			// Right face (x = 1.0f)
			glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
			glVertex3f(1.0f,  1.0f, -1.0f);
			glVertex3f(1.0f,  1.0f,  1.0f);
			glVertex3f(1.0f, -1.0f,  1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();  // End of drawing color-cube
		
	glPopMatrix();
}

void TEnemigo::set_position(glm::vec3 _pos){
	this->m_posicion = _pos;
}

void TEnemigo::restart(){
	m_direccion = 10.0f*RandomVect();
}

TEnemigo::~TEnemigo(){
	
}