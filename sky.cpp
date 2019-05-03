#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "inc/tmanager.h"
#include "inc/camara.h"

#define RED   	0
#define GREEN 	0
#define BLUE  	0
#define ALPHA 	1
#define KEY_ESC 27

float wsize = 600;
float hsize = 600;

int textures_id[6] = {0,0,0,0,0,0};

TCamara *camera;

glm::vec3 etime(0,0,0);
glm::vec2 mouse(0,0);
glm::vec2 delta(0,0);
glm::vec3 center(0,-20,0);

enum textures_name{
	front,
	back,
	left,
	right,
	up,
	down
};

int choose = 1;

void draw_grid(){
	for(float i = -500; i <= 500; i += 5){
		glBegin(GL_LINES);
			glColor3ub(150, 190, 150);
			glVertex3f(-500, 0, i);
			glVertex3f(500, 0, i);
			glVertex3f(i, 0,-500);
			glVertex3f(i, 0, 500);
		glEnd();
	}
}

void draw_skybox(float x, float y, float z, float width, float height, float length){
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, textures_id[front]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, textures_id[back]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, textures_id[left]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, textures_id[right]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, textures_id[up]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, textures_id[down]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
}

void Draw(){
	etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	etime[0] = (etime[2] - etime[1])/1000.0f;	// delta time
	etime[1] = etime[2];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
					camera->m_perspective[2], camera->m_perspective[3]);

	glRotatef(delta.x, 0.0, 1.0, 0.0);
	glRotatef(delta.y, 1.0, 0.0, 0.0);

	gluLookAt(
    	camera->m_posicion.x 					  , camera->m_posicion.y                      , camera->m_posicion.z,
    	camera->m_posicion.x+camera->m_direccion.x, camera->m_posicion.y+camera->m_direccion.y, camera->m_posicion.z+camera->m_direccion.z,
    	0, 1, 0
    );

	draw_grid();
	draw_skybox(0,0,0,300,300,300);	

	glPushMatrix();
		glTranslatef(0,camera->m_posicion.y,0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidSphere(0.5f,10,10);
	glPopMatrix();
	
	glutSwapBuffers();
	glFlush();
}

void WRedraw(GLsizei _w, GLsizei _h){
	glViewport(0, 0, _w, _h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	

	glMatrixMode(GL_MODELVIEW);
}

void Idle(){
	glutPostRedisplay();
}

void Init(void){		
	
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(RED, GREEN, BLUE, ALPHA);
	
	glEnable(GL_TEXTURE_2D);
}


void WKey(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;
        default:
            break;
    }
}

void Mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		mouse.x = x;
		mouse.y = y;
	}
}


void MouseMotion(int x, int y){
	delta.x += (x - mouse.x)/10;
	delta.y += (y - mouse.y)/10;
	
	mouse.x = x;
	mouse.y = y;
	glutPostRedisplay();
}

// g++ sky.cpp src/tmanager.cpp -o sky.out -lGL -lglut -lGLU -lfreeimage
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(wsize, hsize);
	glutInitWindowPosition(50,10);
	glutCreateWindow("SkyBox");
    
    Init();
   
	camera = new TCamara(45, wsize/hsize, 0.01f, 500);
	camera->m_posicion.y = 5.0f;

	textures_id[front] = TextureManager::Inst()->LoadTexture("data/sky/seven/front.jpg", GL_BGR_EXT, GL_RGB);
	textures_id[back]  = TextureManager::Inst()->LoadTexture("data/sky/seven/back.jpg",  GL_BGR_EXT, GL_RGB);
	textures_id[left]  = TextureManager::Inst()->LoadTexture("data/sky/seven/left.jpg",  GL_BGR_EXT, GL_RGB);
	textures_id[right] = TextureManager::Inst()->LoadTexture("data/sky/seven/right.jpg", GL_BGR_EXT, GL_RGB);
	textures_id[up]    = TextureManager::Inst()->LoadTexture("data/sky/seven/up.jpg",    GL_BGR_EXT, GL_RGB);
	textures_id[down]  = TextureManager::Inst()->LoadTexture("data/sky/seven/down.jpg",  GL_BGR_EXT, GL_RGB);	

	/*
	textures_id[front] = TextureManager::Inst()->LoadTexture("data/sky/three/front.png", GL_BGR_EXT, GL_RGB);
	textures_id[back]  = TextureManager::Inst()->LoadTexture("data/sky/three/back.png",  GL_BGR_EXT, GL_RGB);
	textures_id[left]  = TextureManager::Inst()->LoadTexture("data/sky/three/left.png",  GL_BGR_EXT, GL_RGB);
	textures_id[right] = TextureManager::Inst()->LoadTexture("data/sky/three/right.png", GL_BGR_EXT, GL_RGB);
	textures_id[up]    = TextureManager::Inst()->LoadTexture("data/sky/three/up.png",    GL_BGR_EXT, GL_RGB);
	textures_id[down]  = TextureManager::Inst()->LoadTexture("data/sky/three/down.png",  GL_BGR_EXT, GL_RGB);	
	*/

    glutDisplayFunc(&Draw);
    glutReshapeFunc(&WRedraw);

    glutMouseFunc(&Mouse);
	glutMotionFunc(&MouseMotion);

    glutKeyboardFunc(&WKey);
    glutIdleFunc(&Idle);

    glutMainLoop();

    delete camera;
    return 0;
}