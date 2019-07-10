#include "../inc/juego.h"

TMaterial line_material = {
	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
	100.0f
};

int idx_menu = 0;
bool interfaz;

ISoundEngine *SoundEngine = createIrrKlangDevice();
ISoundSource *menu_music  = SoundEngine->addSoundSourceFromFile("data/audio/mountain.wav");
ISoundSource *game_music  = SoundEngine->addSoundSourceFromFile("data/audio/menu.wav");
ISoundSource *door_effect = SoundEngine->addSoundSourceFromFile("data/audio/door.wav");
ISoundSource *gun_effect  = SoundEngine->addSoundSourceFromFile("data/audio/gun.wav");
ISoundSource *jump_effect = SoundEngine->addSoundSourceFromFile("data/audio/jump.wav");



vector<TBoton> TJuego::m_botons;
TJugador *TJuego::m_jugador;
TGestor *TJuego::m_gestor;
glm::vec3 TJuego::m_etime;
TMapa * TJuego::m_mapa;
bool TJuego::salio;



TListener listener;
Controller controller;

int gesture_idx = -1;
bool gesture_state = 0;
int gesture_sentido = 0;

TJuego::TJuego(int &argc, char **argv){
	this->m_ancho = 1000;
	this->m_alto  = 700;
	this->m_num_niveles = 2;
	this->m_cont_n_niveles = 0;

	srand(time(NULL));

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_ancho, m_alto);
    glutInitWindowPosition(50,20);
    glutCreateWindow("Juego!");

    this->m_camara = new TCamara(60, m_ancho/m_alto, 0.01f, 10000);
    this->m_jugador = new TJugador(glm::vec3(0.0f,5.0f,0.0f));
	this->m_jugador->set_camara(m_camara);

    this->m_mapa = new TMapa();
    this->m_gestor = new TGestor();

    this->m_gestor->set_jugador(this->m_jugador);
    this->m_gestor->set_mapa(this->m_mapa);
	

    this->m_gestor->init();

    this->m_luz = {
		glm::vec4(0.0f, 35.0f, 0.0f, 0.0f),	// position
		glm::vec4(0.0f, 0.0f, 0.0f , 1.0f),	// ambient
		glm::vec4(1.0f, 1.0f, 1.0f , 1.0f), // diffuse
		glm::vec4(1.0f, 1.0f, 1.0f , 1.0f)	// specular
	};

	this->m_etime = glm::vec3(0,0,0);
	this->m_mouse = glm::vec3(0,0,0);

	this->m_origen = -1;

	// this->m_audio = new TAudio();
	interfaz = true;
	this->menu_tid = TextureManager::Inst()->LoadTexture("data/texturas/menu.png",  GL_BGRA_EXT, GL_RGBA);

	this->m_botons.push_back(TBoton(glm::vec2(12, 16.5), "Inicio"));
	this->m_botons.push_back(TBoton(glm::vec2(12, 8.5), "Continuar"));
	this->m_botons.push_back(TBoton(glm::vec2(12, 0.5), "Creditos"));
	this->m_botons.push_back(TBoton(glm::vec2(12, -7.5), "Salir"));

	this->salio = false;

	controller.addListener(listener);  

    initGL();
}

TJuego::~TJuego(){
	m_botons.clear();
	m_jugador = NULL;
	m_gestor = NULL;
	m_mapa = NULL;
}

void TJuego::initGL(){
	glClearColor(0, 0, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	// glShadeModel(GL_FLAT);
	// glMatrixMode(GL_PROJECTION);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    // glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(m_luz.m_ambient));

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(m_luz.m_position));
	glLightfv(GL_LIGHT0, GL_AMBIENT , glm::value_ptr(m_luz.m_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE , glm::value_ptr(m_luz.m_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(m_luz.m_specular));

	glMaterialfv(GL_FRONT, GL_AMBIENT,   glm::value_ptr(line_material.m_ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   glm::value_ptr(line_material.m_diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR,  glm::value_ptr(line_material.m_specular));
	glMaterialfv(GL_FRONT, GL_SHININESS, &line_material.m_shininess);

	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	game_music->setDefaultVolume(0.5f);
	menu_music->setDefaultVolume(0.4f);
    
    door_effect->setDefaultVolume(0.3f);
    gun_effect->setDefaultVolume(0.4f);
    jump_effect->setDefaultVolume(0.2f);

    std::thread(leap_gesture).detach();
}

bool fg = false;
bool fm = true;

bool test = true;
bool arrd = false;
int cont = 1;

void TJuego::dibujar(){
	if(interfaz){
		dibujar_ui();
		if(fm){
			SoundEngine->stopAllSounds();
			SoundEngine->play2D(menu_music, true);
			fm = false;
		}
	}
	else{
		if(fg){
			SoundEngine->stopAllSounds();
			SoundEngine->play2D(game_music, true);
			fg = false;
		}
		dibujar_juego();
	}
}

void TJuego::dibujar_ui(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0,0,m_ancho,m_alto);
    gluPerspective( m_camara->m_perspective[0], m_camara->m_perspective[1],
					m_camara->m_perspective[2], m_camara->m_perspective[3]);

    gluLookAt(	0.0f, 0.0f, 50.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);

    glBindTexture(GL_TEXTURE_2D, menu_tid);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1);	glVertex3f(-5,  10, -5.0f);
        glTexCoord2f(0, 1);	glVertex3f(-25,10, -5.0f);
        glTexCoord2f(0, 0);	glVertex3f(-25, -10, -5.0f);
        glTexCoord2f(1, 0); glVertex3f(-5, -10, -5.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, -1);

    for(unsigned i=0; i<m_botons.size(); i++){
    	if(i == idx_menu){
    		m_botons[i].dibujar(glm::vec4(1,0,0,1), glm::vec2(8,3));
    	}
    	else{
    		m_botons[i].dibujar(glm::vec4(1,1,1,1), glm::vec2(8,3));
    	}
    }

	glutSwapBuffers();
	glFlush();
}


/*
    -1 = unknown
    0 = circle
    1 = swipe
    2 = key tap
    3 = screen tap
    4 = fist
	5 = 1 finger
	6 = 2 finger
*/
void TJuego::leap_gesture(){
	bool tmp;
	while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		// cout << gesture_state << ": " << gesture_idx << "\n";
		if(gesture_state){

			switch(gesture_idx){
				case 0:{
					// cout << "circle\n";
					break;
				}
				case 1:{
					// cout << "swipe\n";
					if(!interfaz){
						if(gesture_sentido == 1){
							// cout << "swipe left\n";
							m_jugador->m_camara->m_delta_tangle = 1.0f;
							tmp = true;
						}
						else if(gesture_sentido == 2){
							// cout << "swipe right\n";
							m_jugador->m_camara->m_delta_tangle = -1.0f;
							tmp = true;
						}
						else if(gesture_sentido == 3){
							// cout << "swipe down\n";
							arrd = !arrd;
							m_gestor->arrodillarse_jugador(arrd);
						}
						else if(gesture_sentido == 4){
							// cout << "swipe up\n";
							SoundEngine->play2D(jump_effect);
							m_jugador->m_accion = 1;
							m_jugador->m_velocidad = glm::vec3(0.0f, 10.0f, 0.0f);
						}
					}	
					break;
				}
				case 2:{
					// cout << "key tap\n";
					if(interfaz){
						idx_menu = (idx_menu+1)%(int)m_botons.size();
					}
					break;
				}
				case 4:{
					// cout << "fist\n";
					if(interfaz){
						switch(idx_menu){
							case 0:
							case 1:{
								interfaz = false;
								fg =true;
								break;
							}
							case 2:{
								cout << "Créditos\n";
								break;
							}
							case 3:{
								exit(0);
								break;
							}
						}
					}
					else{
						if(m_mapa->m_cuarto_actual->verificar_puertas(m_jugador, &(m_mapa->m_cuarto_actual), salio)){
							SoundEngine->play2D(door_effect);
							// cout << "Pasando la puerta\n";
						}
					}
					break;
				}
				case 5:{
					if(!interfaz){
						m_jugador->disparar(m_jugador->m_camara->m_direccion, m_etime[0]);
					}
					break;
				}
				default:{
					break;
				}
			}
		}

		gesture_state = false;
	}
}


void TJuego::dibujar_juego(){

	m_etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	m_etime[0] = (m_etime[2] - m_etime[1])/1000.0f;	// delta time
	m_etime[1] = m_etime[2];

	m_camara->actualizar(m_etime[0]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


	if (test){
		m_gestor->dibujar_leyenda();
	}

	glViewport(0,0,m_ancho,m_alto);
    gluPerspective( m_camara->m_perspective[0], m_camara->m_perspective[1],
					m_camara->m_perspective[2], m_camara->m_perspective[3]);
    
    if(!m_camara->m_person){
    	gluLookAt(
	    	m_jugador->m_posicion.x, m_jugador->m_posicion.y, m_jugador->m_posicion.z,
	    	m_jugador->m_posicion.x+m_camara->m_direccion.x, m_jugador->m_posicion.y+m_camara->m_direccion.y, m_jugador->m_posicion.z+m_camara->m_direccion.z,
	    	0, 1, 0
	    );
    }
    else{
    	gluLookAt(
			m_jugador->m_posicion.x-(m_camara->m_direccion.x*20), m_jugador->m_posicion.y+12.0f, m_jugador->m_posicion.z-(m_camara->m_direccion.z*20),
	    	m_jugador->m_posicion.x, m_jugador->m_posicion.y+5.0f, m_jugador->m_posicion.z,
	    	0, 1, 0
	    );
    }

    dibujar_luz(m_luz.m_position, 1, glm::vec4(1,1,1,1));
    m_gestor->set_dt(m_etime[0]);
	if (this->salio == true){
		this->m_gestor->crear_mapa();
		this->m_gestor->init();
		this->m_mapa->m_cuarto_actual = &(this->m_mapa->m_vec_tcuartos[0]);

		//reset jugador
		this->m_jugador->m_vida = 20;
		this->m_jugador->m_mover = 0.0f;	
		this->m_jugador->m_arma = asimple;

		this->m_jugador->armas[asimple] = true;
		this->m_jugador->armas[adoble] = false;
		this->m_jugador->armas[areloj] = false;
		this->m_jugador->armas[arebote] = false;

		this->m_jugador->m_llave = false;
		this->m_jugador->m_posicion.x = 0.0;
		this->m_jugador->m_posicion.z = 0.0;

		this->m_cont_n_niveles += 1;
		this->m_mapa->new_level();
		if (this->m_cont_n_niveles > this->m_num_niveles){
			std::cout << "termino el juego - ganaste!\n";
			interfaz = true;
		}

		this->salio = false;
	}
    m_gestor->dibujar_mapa();
    m_gestor->dibujar_jugador(m_camara->m_direccion);
	m_gestor->dibujar_efectos();
    glutSwapBuffers();
    glFlush();
}


void TJuego::presionar_tecla(unsigned char _t, int _x, int _y){
	switch (_t) {
        case ESC:{
            interfaz = true;
            fm = true;
            break;
		}
		case Q:{
			m_camara->m_person = !m_camara->m_person;
            break;
		}
		case TAB:{
			SoundEngine->play2D(gun_effect);
			m_jugador->cambiar_arma();
			break;
		}
		case ENTER:{
			if(interfaz){
				switch(idx_menu){
					case 0:
					case 1:{
						interfaz = false;
						fg =true;
						break;
					}
					case 2:{
						cout << "Créditos\n";
						break;
					}
					case 3:{
						exit(0);
						break;
					}
				}
			}
			else{
				m_jugador->disparar(m_camara->m_direccion, m_etime[0]);
			}
			break;
		}
        case SPACE:{
        	SoundEngine->play2D(jump_effect);
			m_jugador->m_accion = 1;
			m_jugador->m_velocidad = glm::vec3(0.0f, 10.0f, 0.0f);
			break;
		}
		case W:{
			arrd = !arrd;
			m_gestor->arrodillarse_jugador(arrd);
			break;
		}
		case L:{
			if(cont%2!=0){
				test = true;
			}
			else{
				test = false;
			}
			cont++;
			break;
		}
		case E:{
			if(m_mapa->m_cuarto_actual->verificar_puertas(m_jugador, &(m_mapa->m_cuarto_actual), this->salio)){
				SoundEngine->play2D(door_effect);
				// cout << "Pasando la puerta\n";
			}
			break;
		}
		case C:{
			m_mapa->m_cuarto_actual->m_colision = !m_mapa->m_cuarto_actual->m_colision;
			m_jugador->m_colis = !m_jugador->m_colis;
			break;
		}
        default:
            break;
    }
}

void TJuego::remodelar(GLsizei _w, GLsizei _h){
    this->m_ancho = _w;
    this->m_alto  = _h;

    this->m_camara->m_perspective[1] = _w/_h;

    glViewport(0, 0, m_ancho, m_alto);    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
}

void TJuego::mouse(int button, int state, int x, int y){	
	if (/*state == GLUT_DOWN &&*/button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_UP){
			m_camara->m_angulo += m_camara->m_delta_mangle;
			m_origen = -1;
		}
		else{
			m_origen = x;
		}
	}
	else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){		
		// m_audio->play_sound(0);
		m_jugador->disparar(m_camara->m_direccion, m_etime[0]);
	}
}

void TJuego::mouse_motion(int x, int y){
	if(m_origen >= 0){
		m_camara->m_delta_mangle = (m_origen - x)*0.001f;
		
		m_camara->m_direccion.x = sin(m_camara->m_angulo + m_camara->m_delta_mangle);
		m_camara->m_direccion.z = -cos(m_camara->m_angulo + m_camara->m_delta_mangle);
	}
	// glutPostRedisplay();
}

void TJuego::presionar_tecla_especial(int c, int x, int y){

	switch(c){
		case GLUT_KEY_UP:{			
			if(interfaz){
				idx_menu--;
				if(idx_menu < 0){
					idx_menu = m_botons.size()-1;
				}
			}
			else{
				m_jugador->m_mover = 30.0f;
				m_camara->m_posicion.x += 2;
			}
			
			// std::cout << "up\n";
			// m_audio->play_sound(1);
			break;
		}
		case GLUT_KEY_DOWN:{
			if(interfaz){
				idx_menu = (idx_menu+1)%(int)m_botons.size();
			}
			else{
				m_jugador->m_mover = -30.0f;
				m_camara->m_posicion.x -= 2;
			}
			// std::cout << "down\n";
			// m_audio->play_sound(1);
			break;
		}
		case GLUT_KEY_LEFT:{
			m_camara->m_delta_tangle = 0.7f;
			// std::cout << "left\n";			
			break;
		}
		case GLUT_KEY_RIGHT:{
			// std::cout << "right\n";
			m_camara->m_delta_tangle = -0.7f;
			break;
		}		
		default:
			break;
	}  

	// glutPostRedisplay();
}

void TJuego::soltar_tecla_especial(int c, int x, int y){
	switch(c){
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			m_jugador->m_mover = 0.0f;
			break;
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			m_camara->m_delta_tangle = 0.0f;
			break;
		default:
			break;
	}
}