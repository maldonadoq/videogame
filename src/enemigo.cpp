/*
Contiene el codigo sobre un enemigo, su posicion,
su movimiento, asi como una funcion para dibujarlo
y disparar.
*/

#include "../inc/enemigo.h"

float eno_emit[]    = {1.0, 1.0, 1.0, 1.0};

/*
	Constructor de la clase Enemigo
	posicion del enemigo
*/
TEnemigo::TEnemigo(glm::vec3 _pos){
	this->m_posicion = _pos;
}

/*
	Dibujar el enemigo, modelo y sus balas
	Rotar el enmigo en dirección al jugador
	Dibujar la dimension del jugador
*/
void TEnemigo::dibujar(glm::vec3 _dim, glm::vec3 _centro, bool _col){	
	glPushMatrix();
		float angley = glm::orientedAngle(
							glm::vec2(m_direccion.x, m_direccion.z),
							glm::vec2(m_modelo->m_dir.x, m_modelo->m_dir.z)
						)*180/PI;

		glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
		glRotatef(angley, 0.0f, 1.0f, 0.0f);
		
		if(_col){
			float emit[]    = {0.0, 1.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
				glColor3f(0,1,0);
				glutWireSphere(m_modelo->m_dim/2.0f, 8, 8);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, eno_emit);
		}
		m_modelo->dibujar();
	glPopMatrix();
}

/*
	Actualizar la variable disparar para que en cierto tiempo
	dispare.
*/
void TEnemigo::cargar(float _dt){
	m_tiempo_disparar += _dt;
}

/*
	Dibujar las balas del enemigo, verificar las colisiones con la pared y si es asi,
	eliminar la bala
*/
void TEnemigo::dibujar_balas(glm::vec3 _dim, glm::vec3 _centro, TJugador *_jug){
	int i;
	float emit[]    = {m_color.x, m_color.y, m_color.z, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
	glColor3f(m_color.x,m_color.y,m_color.z);

	bool tcol;
	for(i=0; i<(int)m_balas.size(); i++){
		m_balas[i].dibujar();		

		tcol = _jug->colision(m_balas[i].m_posicion, m_balas[i].m_radio);

		// verificar si colision con el jugador
		if(tcol){
			m_balas.erase(m_balas.begin() + i);
			i--;
		}

		// si colisiona con la pared y no con el jugador
		if(!tcol and !cuarto_colision(_dim, _centro, m_balas[i].m_posicion)){
			m_balas.erase(m_balas.begin() + i);
			i--;
		}		
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, eno_emit);
}

/*
	Verificar la colision del enemigo contra alguien
*/
int TEnemigo::colision(glm::vec3 _pos, float _r){
	int ty = -1;

	float dis = glm::distance(_pos, m_posicion);

	if(dis < (m_modelo->m_dim/2.0f + _r)){
		ty = 1;
		m_vida--;

		if(m_vida <= 0){
			ty = 2;
		}
	}

	return ty;
}

/*
	Dibuja un plano (QUAD) encima del jugador
	que representa el estado del enemigo de acuerdo 
	a sus vidas

	Rotar ese plano siempre en dirección del jugador
	[Billboard!!]
*/
void TEnemigo::barra_vida(glm::vec3 _jug){
	glPushMatrix();
		glm::vec3 tmp = glm::normalize((_jug - glm::vec3(m_posicion.x, _jug.y, m_posicion.z)));
		float angley = glm::orientedAngle(glm::vec2(tmp.x, tmp.z), glm::vec2(m_modelo->m_dir.x, m_modelo->m_dir.z))*180/PI;

		glTranslatef(m_posicion.x, m_posicion.y + (m_modelo->m_dim/2.0f) + 2.0f, m_posicion.z);
		glRotatef(angley, 0.0f, 1.0f, 0.0f);

		float emit[]    = {1.0f,0.0f,0.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
		glColor3f(1.0f,0.0f,0.0f);
			glBegin(GL_QUADS);
				// Front face  (z = 1.0f)
				glVertex3f( 2.0f,  0.25f, 0.0f);
				glVertex3f(-2.0f,  0.25f, 0.0f);
				glVertex3f(-2.0f, -0.25f, 0.0f);
				glVertex3f( 2.0f, -0.25f, 0.0f);
			glEnd();
		
		float l = get_size(4);
		// cout << l << "\n";

		emit[0] = 0.0f;
		emit[1] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
		glColor3f(0.0f,1.0f,0.0f);
			glBegin(GL_QUADS);
				// Front face  (z = 1.0f)
				glVertex3f(-2.0+ l,  0.25f, 0.1f);
				glVertex3f(-2.0f,  0.25f, 0.1f);
				glVertex3f(-2.0f, -0.25f, 0.1f);
				glVertex3f(-2.0 + l, -0.25f, 0.1f);
			glEnd();

		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, eno_emit);
	glPopMatrix();
}

void TEnemigo::set_position(glm::vec3 _pos){
	this->m_posicion = _pos;
}

void TEnemigo::restart(){
	m_direccion = RandomVect();
}

TEnemigo::~TEnemigo(){
	
}