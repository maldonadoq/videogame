#include "../inc/enemigo.h"

TEnemigo::TEnemigo(){

}

TEnemigo::TEnemigo(glm::vec3 _pos): TPersona(_pos){
	this->m_velocidad_inicial = glm::vec3(0.0f, 5.0f, 0.0f);
    this->m_vida = 5;
	this->m_tiempo_disparar = 0;
    this->m_material = {
		glm::vec3(0.0f,0.2f,0.2f),
		RandomColor(),
		glm::vec3(1.0f,1.0f,1.0f),
		0.6f
	};

	this->m_direccion = 10.0f*RandomVect();	
	this->m_color = RandomColor();

	// std::cout << "[" << m_color.x << "," << m_color.y << "," << m_color.z << "]\n";
}

TEnemigo::~TEnemigo(){
}

void TEnemigo::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TEnemigo::dibujar(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , glm::value_ptr(m_material.m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , glm::value_ptr(m_material.m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , glm::value_ptr(m_material.m_specular));
	glMaterialf(GL_FRONT_AND_BACK , GL_SHININESS, m_material. m_shininess);

	glPushMatrix();		
		glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
		
		//cuerpo
		//glColor3f(m_color.x, m_color.y, m_color.z);
		glTranslatef(0.0f ,0.0f, 0.0f);
		glutSolidSphere(4,20,20);

		//cabeza
		glTranslatef(0.0f, 5.5f, 0.0f);
		glutSolidSphere(2,20,20);

		//nariz
		//glColor3f(1.0f, 0.5f , 0.5f);
		glTranslatef(0.0f, 0.0f, 2.0f);
		glRotatef(0.0f,1.0f, 0.0f, 0.0f);
		glutSolidCone(0.5f, 2.0f,10,2);

	glPopMatrix();
}

void TEnemigo::set_posicion_inicial(){
	this->m_posicion_inicial = m_posicion;
}

glm::vec3 TEnemigo::get_posicion(){
	return this->m_posicion;
}

void TEnemigo::anhadir_bala(TBala _bala){
	this->m_balas.push_back(_bala);
}

void TEnemigo::disparar(float _dt, glm::vec3 _dir){
	this->m_tiempo_disparar += _dt;

	if(m_tiempo_disparar > 2.5f){
		TBala tb = {0.4f, m_posicion, _dir};
		m_balas.push_back(tb);
		m_tiempo_disparar = 0;
	}
}