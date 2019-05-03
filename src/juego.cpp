#include "../inc/juego.h"

TJuego::TJuego(int &argc, char **argv){

	this->m_ancho = 600;
	this->m_alto  = 600;

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_ancho, m_alto);
    glutCreateWindow("Juego!");    

    this->m_camara = new TCamara(45, m_ancho/m_alto, 0.01f, 500);
    this->m_jugador = new TJugador(glm::vec3(0,0,0));
    this->m_mapa = new TMapa();

    this->m_gestor = new TGestor();

    this->m_gestor->set_jugador(this->m_jugador);
    this->m_gestor->set_mapa(this->m_mapa);    

    this->m_luz = {
		glm::vec4(0.0f, 20.0f, 0.0f, 1.0f),
		glm::vec4(0.2f, 0.2f, 0.2f , 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f , 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f , 1.0f)
	};

	this->m_etime = glm::vec3(0,0,0);
	this->m_mouse = glm::vec3(0,0,0);

	this->m_origen = -1;

	this->m_audio = new TAudio();

    initGL();
}

TJuego::~TJuego(){

}

void TJuego::initGL(){

	glClearColor(0, 0, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	// glShadeModel(GL_FLAT);
	// glMatrixMode(GL_PROJECTION);
	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();

    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(m_luz.m_ambient));

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(m_luz.m_position));
	glLightfv(GL_LIGHT0, GL_AMBIENT , glm::value_ptr(m_luz.m_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE , glm::value_ptr(m_luz.m_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(m_luz.m_specular));	
}

void TJuego::dibujar(){

	m_etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	m_etime[0] = (m_etime[2] - m_etime[1])/1000.0f;	// delta time
	m_etime[1] = m_etime[2];

	m_camara->actualizar();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( m_camara->m_perspective[0], m_camara->m_perspective[1],
					m_camara->m_perspective[2], m_camara->m_perspective[3]);
    
    gluLookAt(
    	m_jugador->m_posicion.x, m_jugador->m_posicion.y, m_jugador->m_posicion.z,
    	m_jugador->m_posicion.x+m_camara->m_direccion.x, m_jugador->m_posicion.y+m_camara->m_direccion.y, m_jugador->m_posicion.z+m_camara->m_direccion.z,
    	0, 1, 0
    );

    dibujar_luz(m_luz, 1);
    m_gestor->dibujar_mapa();
    m_gestor->dibujar_jugador(m_camara->m_direccion, m_etime[0]);

    glutSwapBuffers();
    glFlush();
}

void TJuego::presionar_tecla(unsigned char _t, int _x, int _y){
	switch (_t) {
        case ESC:{
        	delete this->m_audio;
            exit(0);
            break;
		}
        case SPACE:{
			m_jugador->m_saltar = true;
			m_jugador->set_posicion_inicial();
			break;
		}
        default:
            break;
    }
}

void TJuego::remodelar(GLsizei _w, GLsizei _h){
    this->m_ancho = _w;
    this->m_alto  = _h;

    glViewport(0, 0, m_ancho, m_alto);
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
}

void TJuego::mouse(int button, int state, int x, int y){	
	if (/*state == GLUT_DOWN &&*/button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			m_camara->m_angulo += m_camara->m_delta_mangle;
			m_origen = -1;
		}
		else{
			m_origen = x;
		}
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON){
		TBala tb = {0.4f, m_jugador->m_posicion, m_camara->m_direccion};
		// std::cout << "crear bala\n";
		// std::cout << "balas: " << m_jugador->m_balas.size() << "\n";
		m_audio->play_sound(0);
		m_jugador->anhadir_bala(tb);
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
			m_jugador->m_mover = 0.5f;
			// std::cout << "up\n";
			// m_audio->play_sound(1);
			break;
		}
		case GLUT_KEY_DOWN:{
			m_jugador->m_mover = -0.5f;
			// std::cout << "down\n";
			// m_audio->play_sound(1);
			break;
		}
		case GLUT_KEY_LEFT:{
			m_camara->m_delta_tangle = -0.005f;
			// std::cout << "left\n";			
			break;
		}
		case GLUT_KEY_RIGHT:{
			// std::cout << "right\n";
			m_camara->m_delta_tangle = 0.005f;
			break;
		}		
		default:
			break;
	}	
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