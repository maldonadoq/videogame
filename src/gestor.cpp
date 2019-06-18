#include "../inc/gestor.h"

TGestor::TGestor(){
	this->m_jugador = NULL;
	this->m_mapa = NULL;
	this->m_fuerza = glm::vec3(0.0f, -9.81f, 0.0f);

	m_modelos["monster"]	= new TModelo(3, "data/modelo/monster/monster.obj",	"data/modelo/monster/monster.jpg",	GL_BGR_EXT,		GL_RGB);
	m_modelos["ovni"]		= new TModelo(3, "data/modelo/ufo/ufo.obj",			"data/modelo/ufo/ufo.png",			GL_BGRA_EXT,	GL_RGBA);
	m_modelos["cat"]		= new TModelo(4, "data/modelo/cat/cat.obj",			"data/modelo/cat/cat.jpg",			GL_BGR_EXT,		GL_RGB);
	m_modelos["poly"]		= new TModelo(3, "data/modelo/poly/poly.obj",		"data/modelo/poly/poly.png",		GL_BGR_EXT,		GL_RGB);
	m_modelos["raptor"]		= new TModelo(4, "data/modelo/raptor/raptor.obj",	"data/modelo/raptor/raptor.png",	GL_BGR_EXT,		GL_RGB);
	m_modelos["ogre"]		= new TModelo(4, "data/modelo/ogre/ogre.obj",		"data/modelo/ogre/ogre.png",		GL_BGRA_EXT,	GL_RGBA);
	m_modelos["robbi"]		= new TModelo(3, "data/modelo/robbi/robbi.obj",		"data/modelo/robbi/robbi.png",		GL_BGR_EXT,		GL_RGB);

	m_modelos["barrel"]		= new TModelo(4, "data/modelo/barrel/barrel.obj",	"data/modelo/barrel/barrel.jpg",	GL_BGR_EXT,		GL_RGB);
	m_modelos["chest"]		= new TModelo(3, "data/modelo/chest/chest.obj",		"data/modelo/chest/chest.jpg",		GL_BGR_EXT,		GL_RGB);
	m_modelos["table"]		= new TModelo(4, "data/modelo/table/table.obj",		"data/modelo/table/table.jpg",		GL_BGR_EXT,		GL_RGB);
	m_modelos["heart"]		= new TModelo(4, "data/modelo/heart/heart.obj",		"data/modelo/heart/heart.png",		GL_BGR_EXT,		GL_RGB);
	m_modelos["key"]		= new TModelo(3, "data/modelo/key/key.obj",			"data/modelo/key/key.bmp",			GL_BGR_EXT,		GL_RGB);
	m_modelos["rock"]		= new TModelo(4, "data/modelo/rock/rock.obj",		"data/modelo/rock/rock.png",		GL_BGR_EXT,		GL_RGB);

	// m_modelos["robbi"]		= new TModelo(3, "data/modelo/robbi/robbi.obj",		"data/modelo/robbi/robbi.png",		GL_BGR_EXT,		GL_RGB);
}

void TGestor::set_mapa(TMapa *_mapa){
	this->m_mapa = _mapa;
}

void TGestor::set_jugador(TJugador *_jugador){
	this->m_jugador = _jugador;
	// this->m_jugador->set_modelo(m_modelos["cat"]);
}

void TGestor::dibujar_mapa(){
	this->m_mapa->dibujar(m_dt);
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
		for(j=0; j<(int)m_mapa->m_cuarto_actual->m_enemigos.size(); j++){
			ttype = m_mapa->m_cuarto_actual->m_enemigos[j]->colision(
				m_jugador->m_balas[i].m_posicion,
				m_jugador->m_balas[i].m_radio
			);

			// cout << ttype << "| ";

			if(ttype > 0){
				tcolision = true;
				m_jugador->m_balas.erase(m_jugador->m_balas.begin()+i);
				i--;
				
				if(ttype == 2){
					m_mapa->m_cuarto_actual->m_enemigos.erase(m_mapa->m_cuarto_actual->m_enemigos.begin() + j);
					j--;
				}
				break;
			}
		}

		if(!tcolision and !cuarto_colision(
			m_mapa->m_cuarto_actual->m_dim,
			m_mapa->m_cuarto_actual->m_centro,
			m_jugador->m_balas[i].m_posicion)
		){
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
	if(cuarto_colision(m_mapa->m_cuarto_actual->m_dim, m_mapa->m_cuarto_actual->m_centro, _pos)){
		m_jugador->mover(_pos);
	}
}

void TGestor::init(){
	/*srand(time(NULL));
	int si = m_mapa->m_vec_tcuartos.size();
	m_mapa->m_vec_tcuartos[rand()%si].set_enemigo(new TOvni(glm::vec3(10.0f,15.0f,15.0f), m_modelos["ovni"]));

	m_mapa->m_vec_tcuartos[rand()%si].set_enemigo(new TMonstruo(glm::vec3(23,0.5,10), m_modelos["monster"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_enemigo(new TMonstruo(glm::vec3(-23,0.5,10), m_modelos["poly"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_enemigo(new TMonstruo(glm::vec3(-23,0.5,-10), m_modelos["ogre"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_enemigo(new TMonstruo(glm::vec3(-23,0.5,-15), m_modelos["raptor"]));

	m_mapa->m_vec_tcuartos[rand()%si].set_enemigo(new THydra(glm::vec3(-33,2,15), m_modelos["robbi"]));

	m_mapa->m_vec_tcuartos[rand()%si].set_item(new TItem(glm::vec3(12,3,24), m_modelos["chest"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_item(new TItem(glm::vec3(-12,4,24), m_modelos["key"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_item(new TItem(glm::vec3(-12,3,-24), m_modelos["table"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_item(new TItem(glm::vec3(-12,4,24), m_modelos["heart"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_item(new TItem(glm::vec3(6,2,24), m_modelos["rock"]));
	m_mapa->m_vec_tcuartos[rand()%si].set_item(new TItem(glm::vec3(-25,4,4), m_modelos["barrel"]));*/

	m_mapa->m_cuarto_actual = &m_mapa->m_vec_tcuartos[0];
	m_mapa->m_cuarto_actual->set_jugador(m_jugador);
	m_mapa->m_vec_tcuartos[0].set_enemigo(new THydra(glm::vec3(33,2,0), m_modelos["robbi"]));
	m_mapa->m_vec_tcuartos[0].set_enemigo(new TOvni(glm::vec3(10.0f,15.0f,15.0f), m_modelos["ovni"]));
	m_mapa->m_vec_tcuartos[0].set_enemigo(new TMonstruo(glm::vec3(-23,0.5,-15), m_modelos["raptor"]));
}

void TGestor::dibujar_string(float x, float y, const std::string &s) {
    glRasterPos2f(x, y);
    for (char c: s){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

void TGestor::set_dt(float _dt){
	this->m_dt = _dt;
}

TGestor::~TGestor(){
	m_mapa = NULL;
	m_jugador = NULL;
	m_modelos.clear();
}