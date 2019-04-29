#include "../inc/juego.h"

TJuego::TJuego(int &argc, char **argv){

	this->m_ancho = 600;
	this->m_alto  = 600;

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_ancho, m_alto);
    glutCreateWindow("Juego!");    

    this->m_camara = new TCamara(45, m_ancho/m_alto, 0.01f, 500);
    this->m_mapa = new TMapa();

    this->m_luz = {
		glm::vec4(10.0f, 10.0f, 10.0f, 0.0f),
		glm::vec4(0.2f, 0.2f, 0.2f , 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f , 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f , 1.0f)
	};

	this->m_etime = glm::vec3(0,0,0);
	this->m_delta = glm::vec3(0,0,0);
	this->m_mouse = glm::vec3(0,0,0);

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

	glLightfv(GL_LIGHT0, GL_AMBIENT , glm::value_ptr(m_luz.m_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE , glm::value_ptr(m_luz.m_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(m_luz.m_specular));
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(m_luz.m_position));	
}

void TJuego::dibujar(){

	m_etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	m_etime[0] = (m_etime[2] - m_etime[1])/1000.0f;	// delta time
	m_etime[1] = m_etime[2];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( m_camara->m_perspective[0], m_camara->m_perspective[1],
					m_camara->m_perspective[2], m_camara->m_perspective[3]);

    // glTranslatef(0,0,-75);
	glRotatef(m_delta.x, 0.0, 1.0, 0.0);
	glRotatef(m_delta.y, 1.0, 0.0, 0.0);
    
    /*
    gluLookAt(
    	m_camara->m_posicion.x, m_camara->m_posicion.y, m_camara->m_posicion.z,
    	0, 0, 0,
    	0, 1, 0
    );
    */
    
    m_mapa->dibujar();


    glutSwapBuffers();
    glFlush();
}

void TJuego::tecla_presionada(unsigned char _t, int _x, int _y){
	switch (_t) {
        case ESC:
            exit(0);
            break;
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
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		m_mouse.x = x;
		m_mouse.y = y;
	}
}


void TJuego::mouse_motion(int x, int y){
	m_delta.x += (x - m_mouse.x)/10;
	m_delta.y += (y - m_mouse.y)/10;
	
	m_mouse.x = x;
	m_mouse.y = y;
	glutPostRedisplay();
}