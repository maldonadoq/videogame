#include "../inc/gestor.h"

TGestor::TGestor(){
	this->m_jugador = NULL;
	this->m_mapa = NULL;
	this->m_fuerza = glm::vec3(0.0f, -9.81f, 0.0f);

	m_muebles.push_back(new TModelo(4, "data/modelo/table/table.obj", "data/modelo/table/table.jpg", GL_BGR_EXT, GL_RGB));
	// m_muebles.push_back(new TModelo(3, "data/modelo/chest/chest.obj", "data/modelo/chest/chest.jpg", GL_BGR_EXT, GL_RGB));
}

void TGestor::set_mapa(TMapa *_mapa){
	this->m_mapa = _mapa;
}

void TGestor::set_jugador(TJugador *_jugador){
	this->m_jugador = _jugador;
	// std::cout << "set: " << m_jugador->m_posicion.x << "," << m_jugador->m_posicion.y << "," << m_jugador->m_posicion.z << "\n";
}

void TGestor::dibujar_mapa(){
	this->m_mapa->dibujar();
	for(unsigned i=0; i<m_muebles.size(); i++){
		m_muebles[i]->dibujar();
	}
}

void TGestor::saltar_jugador(){
	if(m_jugador->m_saltar){
		m_jugador->m_velocidad += m_fuerza*m_dt;
		m_jugador->m_posicion += m_jugador->m_velocidad*m_dt;

		if(m_jugador->m_posicion.y < m_jugador->m_piso){
			m_jugador->m_saltar = false;
			m_jugador->m_posicion.y = m_jugador->m_piso;
		}
	}
}

void TGestor::dibujar_balas_jugador(){
	int i, j;
	bool tcolision;
	int ttype;
	for(i=0; i<(int)m_jugador->m_balas.size(); i++){
		glPushMatrix();
			glTranslatef(
				m_jugador->m_balas[i].m_posicion.x,
				m_jugador->m_balas[i].m_posicion.y,
				m_jugador->m_balas[i].m_posicion.z
			);

			glutSolidSphere(m_jugador->m_balas[i].m_radio,8,8);
		glPopMatrix();

		m_jugador->m_balas[i].m_posicion += 10*m_dt*m_jugador->m_balas[i].m_direccion;

		tcolision = false;
		for(j=0; j<(int)m_enemigos.size(); j++){
			ttype = m_enemigos[j]->colision(m_jugador->m_balas[i].m_posicion, m_jugador->m_balas[i].m_radio);

			// cout << ttype << "| ";
			if(ttype > 0){
				tcolision = true;
				m_jugador->m_balas.erase(m_jugador->m_balas.begin()+i);
				i--;

				// cout << "\n" << ttype << "\n";

				if(ttype == 2){
					m_enemigos.erase(m_enemigos.begin() + j);
					j--;
				}
				break;
			}
		}

		if(!tcolision and !cuarto_colision(m_mapa->m_cuarto_actual->m_dim, m_mapa->m_cuarto_actual->m_centro, m_jugador->m_balas[i].m_posicion)){
			m_jugador->m_balas.erase(m_jugador->m_balas.begin()+i);
			i--;
		}
	}
}

void TGestor::dibujar_jugador(glm::vec3 _dir){
	if(m_jugador->m_mover){
		mover_jugador(m_dt*_dir*m_jugador->m_mover);
	}

	if(m_jugador->m_saltar){
		saltar_jugador();
	}

	dibujar_balas_jugador();
	this->m_jugador->dibujar();
}

void TGestor::mover_jugador(glm::vec3 _dir){
	glm::vec3 _pos = m_jugador->m_posicion+_dir;
	//if(cuarto_colision(m_mapa->m_cuarto_actual->m_dim, m_mapa->m_cuarto_actual->m_centro, _pos)){
		m_jugador->mover(_pos);
	//}
}

void TGestor::crear_enemigos(unsigned _n){
	m_enemigos.push_back(new TOvni(RandomPosition(m_mapa->m_cuarto_dim.x/2, 13, m_mapa->m_cuarto_dim.z/2)));
	m_enemigos.push_back(new TMonstruo(RandomPosition(m_mapa->m_cuarto_dim.x/2, 3, m_mapa->m_cuarto_dim.z/2)));
}

void TGestor::dibujar_enemigos(){
	// mover_enemigos();
	for(unsigned i=0; i<m_enemigos.size(); i++){
		m_enemigos[i]->mover(m_mapa->m_cuarto_actual->m_dim, m_mapa->m_cuarto_actual->m_centro, m_dt);
		m_enemigos[i]->dibujar(m_mapa->m_cuarto_actual->m_dim, m_mapa->m_cuarto_actual->m_centro);
		m_enemigos[i]->cargar(m_dt);
		m_enemigos[i]->disparar(m_jugador->m_posicion, m_dt);
	}
}

void TGestor::set_dt(float _dt){
	this->m_dt = _dt;
}

TGestor::~TGestor(){
	m_mapa = NULL;
	m_jugador = NULL;
	m_enemigos.clear();
	m_muebles.clear();
}