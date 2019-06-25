#include "../inc/gestor.h"
#include <string>

float jno_emit[]    = {1.0, 1.0, 1.0, 1.0};

/*
	Constructor de la clase Gestor
	Cargamos los modelos de los enemigos que existirán en el mapa
*/
TGestor::TGestor(){
	this->m_jugador = NULL;
	this->m_mapa = NULL;
	this->m_fuerza = glm::vec3(0.0f, -9.81f, 0.0f);

	/*m_modelos["monster"]	= new TModelo(3, "data/modelo/monster/monster.obj",	"data/modelo/monster/monster.tga",	GL_BGRA_EXT,	GL_RGBA);
	m_modelos["ovni"]		= new TModelo(3, "data/modelo/ufo/ufo.obj",			"data/modelo/ufo/ufo.png",			GL_BGRA_EXT,	GL_RGBA);
	m_modelos["poly"]		= new TModelo(3, "data/modelo/poly/poly.obj",		"data/modelo/poly/poly.png",		GL_BGR_EXT,		GL_RGB);
	m_modelos["raptor"]		= new TModelo(4, "data/modelo/raptor/raptor.obj",	"data/modelo/raptor/raptor.png",	GL_BGR_EXT,		GL_RGB);
	m_modelos["ogre"]		= new TModelo(4, "data/modelo/ogre/ogre.obj",		"data/modelo/ogre/ogre.png",		GL_BGRA_EXT,	GL_RGBA);
	m_modelos["robbi"]		= new TModelo(3, "data/modelo/robbi/robbi.obj",		"data/modelo/robbi/robbi.png",		GL_BGR_EXT,		GL_RGB);
	m_modelos["sentinel"]	= new TModelo(3, "data/modelo/sentinel/sentinel.obj",	"data/modelo/sentinel/sentinel.jpg",	GL_BGR_EXT,		GL_RGB);
	m_modelos["iron"]		= new TModelo(3, "data/modelo/iron/iron.obj",			"data/modelo/iron/iron.png",		GL_BGR_EXT,		GL_RGB);

	m_modelos["barrel"]		= new TModelo(4, "data/modelo/barrel/barrel.obj",	"data/modelo/barrel/barrel.jpg",	GL_BGR_EXT,		GL_RGB);
	m_modelos["chest"]		= new TModelo(3, "data/modelo/chest/chest.obj",		"data/modelo/chest/chest.jpg",		GL_BGR_EXT,		GL_RGB);
	m_modelos["table"]		= new TModelo(4, "data/modelo/table/table.obj",		"data/modelo/table/table.jpg",		GL_BGR_EXT,		GL_RGB);
	m_modelos["heart"]		= new TModelo(4, "data/modelo/heart/heart.obj",		"data/modelo/heart/heart.png",		GL_BGR_EXT,		GL_RGB);
	m_modelos["key"]		= new TModelo(3, "data/modelo/key/key.obj",			"data/modelo/key/key.bmp",			GL_BGR_EXT,		GL_RGB);*/

	m_modelos["rock"]		= new TModelo(4, "data/modelo/rock/rock.obj",		"data/modelo/rock/rock.png",		GL_BGR_EXT,		GL_RGB);*/
	m_modelos["robbi"]		= new TModelo(3, "data/modelo/robbi/robbi.obj",		"data/modelo/robbi/robbi.png",		GL_BGR_EXT,		GL_RGB);
	m_modelos["raptor"]		= new TModelo(4, "data/modelo/raptor/raptor.obj",	"data/modelo/raptor/raptor.png",	GL_BGR_EXT,		GL_RGB);
	m_modelos["sentinel"]	= new TModelo(3, "data/modelo/sentinel/sentinel.obj",	"data/modelo/sentinel/sentinel.jpg",	GL_BGR_EXT,		GL_RGB);
	m_modelos["chest"]		= new TModelo(3, "data/modelo/chest/chest.obj",		"data/modelo/chest/chest.jpg",		GL_BGR_EXT,		GL_RGB);
}

/*
	Metodo para setear el mapa, es un puntero que pertenece a la clase Juego
*/
void TGestor::set_mapa(TMapa *_mapa){
	this->m_mapa = _mapa;
}

/*
	Metodo para setear el jugador en el gestor,
	es un puntero que pertenece a la clase Juego
*/
void TGestor::set_jugador(TJugador *_jugador){
	this->m_jugador = _jugador;
	this->m_jugador->set_modelo(m_modelos["iron"]);
}

/*
	Metodo que llamará a la función dibujar del mapa
*/
void TGestor::dibujar_mapa(){
	this->m_mapa->dibujar(m_dt);
}

/*
	Metodos que permite que el jugador pueda salta, aplicando la gravedad
*/
void TGestor::saltar_jugador(){
	m_jugador->m_velocidad += m_fuerza*m_dt;
	m_jugador->m_posicion += m_jugador->m_velocidad*m_dt;

	if(m_jugador->m_posicion.y < m_jugador->m_piso){
		m_jugador->m_accion = -1;
		m_jugador->m_posicion.y = m_jugador->m_piso;
	}
}

/*
	Dibuja las balas del jugador, verificando si colision con un enemigo o con las paredes
	Si colisiona con alguien la bala de elimina, si colisiona con un enemigo, se le descuenta
	la vida a este mismo,
*/
void TGestor::dibujar_balas_jugador(){
	int i, j;
	bool tcolision;
	int ttype;

	float emit[]    = {0.0f, 0.0f, 0.0f, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
	glColor3f(0.0f, 0.0f, 0.0f);
	for(i=0; i<(int)m_jugador->m_balas.size(); i++){
		m_jugador->m_balas[i]->dibujar();

		tcolision = false;
		for(j=0; j<(int)m_mapa->m_cuarto_actual->m_enemigos.size(); j++){
			ttype = m_mapa->m_cuarto_actual->m_enemigos[j]->colision(
				m_jugador->m_balas[i]->m_posicion,
				m_jugador->m_balas[i]->m_radio
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
		
		if(!tcolision and 	!m_jugador->m_balas[i]->paredes(
							m_mapa->m_cuarto_actual->m_dim,
							m_mapa->m_cuarto_actual->m_centro)
		){	
			delete m_jugador->m_balas[i];
			m_jugador->m_balas.erase(m_jugador->m_balas.begin()+i);
			i--;
		}
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, jno_emit);
}

/*
	Metodo que llama a las funciones 
		mover_jugador
		saltar_jugador
		dibujar_balas_jugador
		dibujar (clase jugador)
*/
void TGestor::dibujar_jugador(glm::vec3 _dir){
	if(m_jugador->m_mover){
		mover_jugador(m_dt*_dir*m_jugador->m_mover);
	}

	if(m_jugador->m_accion == 3){
		saltar_jugador();
	}

	dibujar_balas_jugador();
	
	this->m_jugador->dibujar();
}

/*
	Mover el jugador en el cuarto en un direccion dada
	Verificando que no pase de las paredes
*/
void TGestor::mover_jugador(glm::vec3 _dir){
	glm::vec3 _pos = m_jugador->m_posicion+_dir;

	glm::vec3 tmp = glm::vec3(m_jugador->m_modelo->m_dim, m_jugador->m_modelo->m_dim/2.0f, m_jugador->m_modelo->m_dim);
	if(cuarto_colision(m_mapa->m_cuarto_actual->m_dim - tmp, m_mapa->m_cuarto_actual->m_centro, _pos)){
		m_jugador->mover(_pos);
	}
}

/*
	Iniciar el el mapa en el gestor
	Crear enemigos en cuartos aleatorios
*/
void TGestor::init(){
	std::vector<std::string> lista_enemigos = {"raptor", "robbi", "sentinel"};
	int idx_enemigo = 0;

	for (int i = 0; i < m_mapa->m_vec_tcuartos.size(); ++i){
		if (m_mapa->m_vec_tcuartos[i].m_tipo == "entrada"){
			m_mapa->m_cuarto_actual = &m_mapa->m_vec_tcuartos[i];
			m_mapa->m_cuarto_actual->set_jugador(m_jugador);
			m_mapa->m_vec_tcuartos[i].set_enemigo(new TMonstruo(glm::vec3(15,0.5,-15), m_modelos["raptor"]));
			m_mapa->m_vec_tcuartos[i].set_enemigo(new THydra(glm::vec3(-33,2,15), m_modelos["robbi"]));
			m_mapa->m_vec_tcuartos[i].set_enemigo(new TSentinel(glm::vec3(33,2,15), m_modelos["sentinel"]));
			
		}
		else if (m_mapa->m_vec_tcuartos[i].m_tipo == "salida"){
			//boss que impide salir
		}
		else if (m_mapa->m_vec_tcuartos[i].m_tipo == "normal"){
			if (lista_enemigos[idx_enemigo] == "raptor"){
				m_mapa->m_vec_tcuartos[i].set_enemigo(new TMonstruo(glm::vec3(15,0.5,-15), m_modelos["raptor"]));
			}
			else if (lista_enemigos[idx_enemigo] == "robbi"){
				m_mapa->m_vec_tcuartos[i].set_enemigo(new THydra(glm::vec3(-33,2,15), m_modelos["robbi"]));
			}
			else if (lista_enemigos[idx_enemigo] == "sentinel"){
				m_mapa->m_vec_tcuartos[i].set_enemigo(new TSentinel(glm::vec3(33,2,15), m_modelos["sentinel"]));
			}
			++idx_enemigo;
			if (idx_enemigo == lista_enemigos.size()){
				idx_enemigo = 0;
			}
		}
		else if (m_mapa->m_vec_tcuartos[i].m_tipo == "tesoro"){
			m_mapa->m_vec_tcuartos[i].set_item(new TItem(glm::vec3(0,2,0), m_modelos["chest"]));

			if (lista_enemigos[idx_enemigo] == "raptor"){
				m_mapa->m_vec_tcuartos[i].set_enemigo(new TMonstruo(glm::vec3(15,0.5,-15), m_modelos["raptor"]));
			}
			else if (lista_enemigos[idx_enemigo] == "robbi"){
				m_mapa->m_vec_tcuartos[i].set_enemigo(new THydra(glm::vec3(-33,2,15), m_modelos["robbi"]));
			}
			else if (lista_enemigos[idx_enemigo] == "sentinel"){
				m_mapa->m_vec_tcuartos[i].set_enemigo(new TSentinel(glm::vec3(33,2,15), m_modelos["sentinel"]));
			}
			++idx_enemigo;
			if (idx_enemigo == lista_enemigos.size()){
				idx_enemigo = 0;
			}
		}
		else if (m_mapa->m_vec_tcuartos[i].m_tipo == "llave dorada"){
			//boss, cuando lo matas aparece la llave dorada
		}
	}
}

void drawBitmapText(const std::string &s,float x,float y){  
	glRasterPos2f(x, y);
	for (char c: s){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
	}
}

void TGestor::dibujar_leyenda() {
	glViewport(0,600,100,100);
	glPushMatrix();
		gluOrtho2D(0,100,0,100); 
		string vida="Vida: "+to_string(m_jugador->m_vida);
		string balas="Numero de Balas: " + to_string(m_jugador->m_balas.size());

		drawBitmapText(vida,10,50);
		drawBitmapText(balas,10,30);
	glPopMatrix();
}

/*
	Seteear el delta time para el gestor
*/
void TGestor::set_dt(float _dt){
	this->m_dt = _dt;
}

TGestor::~TGestor(){
	m_mapa = NULL;
	m_jugador = NULL;
	m_modelos.clear();
}