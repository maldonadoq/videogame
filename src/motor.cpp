#include "../inc/motor.h"

/*
    Constructor de la clase Particula
    solo tiene un metodo, que es el iniciar de la particula
*/
TParticula::TParticula(){
    this->m_posicion = glm::vec3(0);
    this->m_velocidad = glm::vec3(0);
    this->m_rotate = 0;
    this->m_age = 0;
    this->m_life_time = 0;
}

TParticula::~TParticula(){

}

/*
    Iniciar la particula con un daterminada posición!
    El tiempo de vida está entre un rango [0.5 , 2.0] s
    Velocidad inicial 3.5 m/s
*/
void TParticula::init(glm::vec3 _pos){
    m_age = 0;
	m_life_time = RandomBeetwen(0.5f, 2.0f);

	m_posicion	= _pos;
	m_velocidad	=  glm::vec3(0,3.5,0);
	m_size		= RandomBeetwen(0.5,2);
}

/*
    Función para comparar las particulas, necesario para el sort 
    de STL
*/
bool CompararParticula(TParticula  p1, TParticula p2) {
    return p1.m_distancia > p2.m_distancia;
}

/*
    Contructor por defctor de la clase Motor
*/
TMotor::TMotor(){

}

/*
    Contructor de la clase Motor
    Se crea n particulas, asignando las posiciones random respecto a un punto
*/
TMotor::TMotor(glm::vec3 _pos, float _range, int _num){
    this->m_centro = _pos;
    this->m_fuerza = glm::vec3(0,-4.8,0);
    this->m_particulas.resize(_num);

    for(int i=0; i<_num; i++){
        m_particulas[i].init(glm::vec3( _pos.x + RandomBeetwen(-_range, _range),
                                        _pos.y + RandomBeetwen(-_range, _range),
                                        _pos.z + RandomBeetwen(-_range, _range)
                                    ));
    }    
}

/*
    Dibujar el sistema de particulas
    Rotar los quad de las particulas hacia el jugador
    Calcular la distancia hacia el jugador y luego ordenarlas 
    para hacer uso de las transparencias
*/
void TMotor::render(glm::vec3 _pos, int _idt){
    glm::vec3 tmp = glm::normalize((_pos - glm::vec3(m_centro.x, _pos.y, m_centro.z)));
	float _angle = glm::orientedAngle(glm::vec2(tmp.x, tmp.z), glm::vec2(0,1))*180/PI;

    unsigned i;
    for(i=0; i<m_particulas.size(); i++){
        m_particulas[i].m_distancia = glm::distance(_pos, m_particulas[i].m_posicion);
    }

    sort(m_particulas.begin(), m_particulas.end(), CompararParticula);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, _idt);
    for(i=0; i<m_particulas.size(); i++){
		glPushMatrix();
			glTranslatef(
				m_particulas[i].m_posicion.x,
				m_particulas[i].m_posicion.y,
				m_particulas[i].m_posicion.z
			);
            glRotatef(_angle, 0.0f, 1.0f, 0.0f);

            glBegin(GL_QUADS);
                glTexCoord2f(1, 1);
				glVertex3f(m_particulas[i].m_size,   m_particulas[i].m_size, 0.0f);
                glTexCoord2f(0, 1);
				glVertex3f(-m_particulas[i].m_size,  m_particulas[i].m_size, 0.0f);
                glTexCoord2f(0, 0);
				glVertex3f(-m_particulas[i].m_size, -m_particulas[i].m_size, 0.0f);
                glTexCoord2f(1, 0);
				glVertex3f(m_particulas[i].m_size,  -m_particulas[i].m_size, 0.0f);
			glEnd();
		glPopMatrix();
	}
    glDisable(GL_BLEND);
}

/*
    Actualizar el sistema de particulas
    respecto a una fuerza (gravedad), se hace uso del 
    delta time
*/
void TMotor::update(float _dt){
    for(int i=0; i<(int)m_particulas.size(); i++){
        m_particulas[i].m_age += _dt;
        if(m_particulas[i].m_age > m_particulas[i].m_life_time){
            m_particulas.erase(m_particulas.begin() + i);
            i--;
        }
        else{
            m_particulas[i].m_velocidad += m_fuerza*_dt;
            m_particulas[i].m_posicion += m_particulas[i].m_velocidad*_dt;
        }
    }
}

unsigned TMotor::size(){
    return m_particulas.size();
}

TMotor::~TMotor(){

}