#include "../inc/jugador.h"

string armas_nombre[4] = {"Revolver K47 [Normal]", "Zoraki 914 [2 Disparos]", "Metralleta R-12 [12 Disparos Reloj]", "QBZ-95 [Bala con Rebote]"};

float no_juemit[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float juemit[4] = {0.0f, 1.0f, 0.0f, 1.0f};

TJugador::TJugador(){

}

TJugador::TJugador(glm::vec3 _pos){
	this->m_posicion = _pos;
	this->m_piso = m_posicion.y;
	this->m_vida = 20;
	this->m_mover = 0.0f;	
	this->m_arma = asimple;

	this->armas[asimple] = true;
	this->armas[adoble] = false;
	this->armas[areloj] = false;
	this->armas[arebote] = false;

	this->m_llave = false;
	this->m_colis = true;
}

TJugador::~TJugador(){
	
}

void TJugador::mover(glm::vec3 _pos){
	m_posicion = _pos;
}

void TJugador::dibujar(){
	if(m_camara->m_person){
		glm::vec2 a(m_camara->m_direccion.x, m_camara->m_direccion.z);
		glm::vec2 b(m_modelo->m_dir.x, m_modelo->m_dir.z);
		float angley = glm::orientedAngle(a, b)*180/PI;
		glPushMatrix();
			glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
			glRotatef(angley, 0.0f, 1.0f, 0.0f);

			if(m_colis){
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, juemit);
					glColor3f(0,1,0);
					glutWireSphere(m_modelo->m_dim/2.0f, 8, 8);

				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_juemit);
			}
			m_modelo->dibujar();
		glPopMatrix();
	}

	/*glBegin(GL_LINES);
		glVertex3f(m_posicion.x, m_posicion.y, m_posicion.z);
		glVertex3f(	m_posicion.x + (m_camara->m_direccion.x*50),
					m_posicion.y + (m_camara->m_direccion.y*50),
					m_posicion.z + (m_camara->m_direccion.z*50)
				  );
	glEnd();*/
}

void TJugador::set_modelo(TModelo *_model){
	this->m_modelo = _model;
	this->m_posicion.y += m_modelo->m_dim/2.0f;
	this->m_piso = m_posicion.y;
}

void TJugador::set_camara(TCamara *_camara){
	this->m_camara = _camara;
}

glm::vec3 TJugador::get_posicion(){
	return this->m_posicion;
}

/*
	Cambiar el tipo de arma que tenemos activadas
*/
void TJugador::cambiar_arma(){
	do{
		m_arma = (m_arma+1)%4;
	}while(!armas[m_arma]);
	// cout << armas_nombre[m_arma] << " elegida\n";
}

/*
	Activar arma al encontrar se llama
	cuando el jugador pasa sobre ese 
	item de arma
*/
void TJugador::set_arma(int i){
	armas[i] = true;
	m_arma = i;
}

/*
	Devuelve el tipo de arma que tiene 
	el jugador
*/
string TJugador::get_arma(){
	return armas_nombre[m_arma];
}

string TJugador::get_llave(){
	return (m_llave)? "True": "False";
}

/*
	Metodo que se llama cuando se hace click en el boton derecho
	segun el tipo de arma que haya sido seleccionado con la tecla TAB
	se añade un bala.
		asimple: un solo disparo
		adoble : dos disparos a la vez
		areloj : disparo en direccion de las agujas del reloj
		arebote: disparo simple, pero que rebota k veces en las paredes
*/
void TJugador::disparar(glm::vec3 _dir, float _dt){
	switch (m_arma){
		case asimple:{
			m_balas.push_back(new TBala(0.2f, m_posicion+(m_camara->m_direccion*3.0f), m_camara->m_direccion*_dt*50.0f));
			break;
		}
		case adoble:{
			m_balas.push_back(new TBala(0.2f, m_posicion+(m_camara->m_direccion*10.0f), m_camara->m_direccion*_dt*60.0f));
			m_balas.push_back(new TBala(0.2f, m_posicion+(m_camara->m_direccion), m_camara->m_direccion*_dt*60.0f));
			break;
		}
		case areloj:{
			float x, z, theta;    		
	        glm::vec3 tmp;
	        tmp.y = 0;
			for(int i = 0; i < 12; i++){
			    theta = (float)(2*PI*i)/12;
			    tmp.x = cos(theta);
			    tmp.z = sin(theta);

	            m_balas.push_back(new TBala(0.2f, m_posicion, tmp*_dt*60.0f));
			}
			break;
		}
		case arebote:{
			m_balas.push_back(new TReal(0.2f, m_posicion+(m_camara->m_direccion*10.0f), m_camara->m_direccion*_dt*40.0f));
			break;
		}
		default:
			break;
	}
}
/*
	Método para verificar si existe una colision de una bala con
	el jugador, teniendo en cuenta la dimensión de la bala y el jugador
*/
bool TJugador::colision(glm::vec3 _pos, float _r){
	float dis = glm::distance(_pos, m_posicion);

	if(dis < (m_modelo->m_dim/2.0f + _r)){
		m_vida--;
		return true;
	}

	return false;
}