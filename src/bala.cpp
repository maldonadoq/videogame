#include "../inc/bala.h"

/*
	Constructor de la clase Bala
	radio = dimension de la bala
	posición = posicion de la bala
	dirección = hacia donde se dirige
*/
TBala::TBala(float _radio, glm::vec3 _position, glm::vec3 _direccion){
	this->m_radio = _radio;
	this->m_posicion = _position;
	this->m_direccion = _direccion;
}

/*
	Contructor por defecto
*/
TBala::TBala(){

}

/*
	Dibujar el movimiento de la bala
	actualizando la posicion respecto a la dirección
*/
void TBala::dibujar(){
	glPushMatrix();
		glTranslatef(m_posicion.x, m_posicion.y, m_posicion.z);
		glutSolidSphere(m_radio,8,8);
	glPopMatrix();

	m_posicion += m_direccion;
}

/*
	Colision con las paredes
	Tipo de bala normal
*/
bool TBala::paredes(glm::vec3 _dim, glm::vec3 _cen){
	return cuarto_colision(_dim, _cen, m_posicion);
}



/*
	Tipo de bala con rebote
	Constructor por defecto heredado de la clase TBala
*/
TReal::TReal(): TBala(){
	this->m_rebotes = 2;
}

/*
	Tipo de bala con rebote
	Constructor heredado de la clase TBala
*/
TReal::TReal(float _r, glm::vec3 _pos, glm::vec3 _dir): TBala(_r, _pos, _dir){
	this->m_rebotes = 2;
}

/*
	Colision con las paredes, ver hacia donde rebota esta
	Rebota con la pared.
*/
bool TReal::paredes(glm::vec3 _dim, glm::vec3 _cen){
	glm::vec2 tmp;
	bool choque = cuarto_colision(_dim, _cen, m_posicion, tmp);
	if(!choque){
		if(m_rebotes > 0){
			m_rebotes--;
			m_direccion.x *= tmp.x;
			m_direccion.z *= tmp.y;			
			return true;
		}
		else{
			return false;
		}
	}

	return true;
}