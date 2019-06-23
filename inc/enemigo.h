#ifndef _ENEMIGO_H_
#define _ENEMIGO_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <vector>
#include <math.h>
#include "bala.h"
#include "utils.h"
#include "modelo.h"
#include "random.h"

using std::cout;
using std::vector;

enum TEnemVida{
	emonstruo	= 15,
	ehydra		= 10,
	eovni		= 12,
	esentinel	= 8
};

class TEnemigo{
protected:
	float m_tiempo_disparar;
	glm::vec3 m_color;		// balas
public:
	TModelo * m_modelo;
	glm::vec3 m_direccion;

    vector<TBala> m_balas;
	
	glm::vec3 m_posicion_inicial;
	glm::vec3 m_velocidad;
	glm::vec3 m_posicion;

    int m_vida;
    
    TEnemigo(glm::vec3);
	TEnemigo();
    virtual ~TEnemigo();
	
	void anhadir_bala(TBala);
	void barra_vida(glm::vec3);
	void restart();
	void cargar(float);					// espera para disparar de nuevo
	void set_position(glm::vec3);

	void dibujar_balas(glm::vec3, glm::vec3);
	
	virtual void dibujar(glm::vec3, glm::vec3, bool);
	virtual int  colision(glm::vec3, float);
	
	virtual void mover(glm::vec3, glm::vec3, glm::vec3, float) = 0;
	virtual void disparar(glm::vec3, float) = 0;
	virtual float get_size(float) = 0;

	friend std::ostream& operator<< (std::ostream & out, const TEnemigo &p){
       out << "[" << p.m_posicion.x << "," << p.m_posicion.y << "," << p.m_posicion.z << "]";
       return out;
   	}
};

#endif