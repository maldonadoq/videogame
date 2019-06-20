#include "../inc/monstruo.h"

TMonstruo::TMonstruo(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = 5;
    this->m_direccion = 10.0f*RandomVect();
    this->m_modelo = _model;
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion += (m_modelo->m_dim/2.0f);
}

void TMonstruo::mover(glm::vec3 _jug, glm::vec3 _dim, glm::vec3 _centro, float _dt){
    m_direccion = glm::normalize((_jug - glm::vec3(m_posicion.x, _jug.y, m_posicion.z)));
    glm::vec3 _pos = m_posicion + (m_direccion*_dt*3.0f);

    if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
        if(glm::distance(m_posicion, _jug) < (3*m_modelo->m_dim)){
            m_posicion = _pos;
            disparar(_jug, _dt);
        }
    }
}

void TMonstruo::dibujar(glm::vec3 _dim, glm::vec3 _centro, bool _col){
    glPushMatrix();
        glTranslatef(m_posicion.x, m_posicion.y-2.0f, m_posicion.z);
        if(_col){
			float emit[]    = {0.0, 0.0, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
			glColor3f(0,0,1);
			draw_circle(m_modelo->m_dim*3.0f, 8);
		}
    glPopMatrix();
    TEnemigo::dibujar(_dim, _centro, _col);
}

void TMonstruo::disparar(glm::vec3 _pos, float _dt){
	if(m_tiempo_disparar > 2.5f){
        // std::cout << "shoot!\n";
        glm::vec3 _dir = glm::normalize(_pos - m_posicion)*_dt*50.0f;
		TBala tb = {0.2f, m_posicion, _dir};

		m_balas.push_back(tb);
		m_tiempo_disparar = 0.0f;
	}
}