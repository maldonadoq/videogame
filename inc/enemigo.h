#ifndef _ENEMIGO_H_
#define _ENEMIGO_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "bala.h"
#include "utils.h"
#include "modelo.h"
#include "random.h"

class TEnemigo{
protected:
	float m_tiempo_disparar;
public:
	TModelo * m_modelo;
	glm::vec3 m_direccion;

    std::vector<TBala> m_balas;
	
	glm::vec3 m_posicion_inicial;
	glm::vec3 m_velocidad;
	glm::vec3 m_posicion;

    int m_vida;
    
    TEnemigo(glm::vec3 _pos);
	TEnemigo();
    virtual ~TEnemigo();
	
	void anhadir_bala(TBala);
	void barra_vida();
	void restart();
	void cargar(float);					// espera para disparar de nuevo
	void set_position(glm::vec3);

	void dibujar(glm::vec3, glm::vec3);
	void dibujar_balas(glm::vec3, glm::vec3);
	int  colision(glm::vec3, float);

	virtual glm::vec3 mover(glm::vec3, glm::vec3, float) = 0;
	// virtual void disparar(glm::vec3) = 0;
	virtual void disparar(glm::vec3, float) = 0;

	friend std::ostream& operator<< (std::ostream & out, const TEnemigo &p){
       out << "[" << p.m_posicion.x << "," << p.m_posicion.y << "," << p.m_posicion.z << "]";
       return out;
   	}
};

#endif