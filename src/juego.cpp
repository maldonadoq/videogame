#include "../inc/juego.h"

TMaterial line_material = {
	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
	100.0f
};

int idx_menu = 0;

TJuego::TJuego(int &argc, char **argv){
	this->m_ancho = 1000;
	this->m_alto  = 700;

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_ancho, m_alto);
    glutInitWindowPosition(50,20);
    glutCreateWindow("Juego!");

    this->m_camara = new TCamara(60, m_ancho/m_alto, 0.01f, 2500);
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
	this->interfaz = true;
	this->menu_tid = TextureManager::Inst()->LoadTexture("data/texturas/menu.png",  GL_BGRA_EXT, GL_RGBA);

	this->m_botons.push_back(TBoton(glm::vec2(12, 16.5), "Inicio"));
	this->m_botons.push_back(TBoton(glm::vec2(12, 8.5), "Continuar"));
	this->m_botons.push_back(TBoton(glm::vec2(12, 0.5), "Creditos"));
	this->m_botons.push_back(TBoton(glm::vec2(12, -7.5), "Salir"));

    initGL();
}

TJuego::~TJuego(){
	m_botons.clear();
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
}

bool test = true;
bool arrd = false;
int cont = 1;

void TJuego::dibujar(){
	if(interfaz){
		dibujar_ui();
	}
	else{
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

    dibujar_luz(m_luz, 1);
    m_gestor->set_dt(m_etime[0]);
    m_gestor->dibujar_mapa();
    m_gestor->dibujar_jugador(m_camara->m_direccion);
	m_gestor->dibujar_efectos();
    glutSwapBuffers();
    glFlush();
}

void TJuego::presionar_tecla(unsigned char _t, int _x, int _y){
	switch (_t) {
        case ESC:{
        	/*delete this->m_audio;
            exit(0);*/
            interfaz = !interfaz;
            break;
		}
		case Q:{
			m_camara->m_person = !m_camara->m_person;
            break;
		}
		case TAB:{			
			m_jugador->cambiar_arma();
			break;
		}
		case ENTER:{
			if(interfaz){
				switch(idx_menu){
					case 0:
					case 1:{
						interfaz = false;
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
			m_mapa->m_cuarto_actual->verificar_puertas(m_jugador, &(m_mapa->m_cuarto_actual));
			break;
		}
		case C:{
			m_mapa->m_cuarto_actual->m_colision = !m_mapa->m_cuarto_actual->m_colision;
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
				m_jugador->m_mover = 20.0f;
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
				m_jugador->m_mover = -20.0f;
				m_camara->m_posicion.x -= 2;
			}
			// std::cout << "down\n";
			// m_audio->play_sound(1);
			break;
		}
		case GLUT_KEY_LEFT:{
			m_camara->m_delta_tangle = 0.5f;
			// std::cout << "left\n";			
			break;
		}
		case GLUT_KEY_RIGHT:{
			// std::cout << "right\n";
			m_camara->m_delta_tangle = -0.5f;
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