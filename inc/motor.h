#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include "random.h"
#include "utils.h"

using std::vector;

class TParticula{
public:	
	glm::vec3   m_posicion;     // Center point of particle
    glm::vec3   m_velocidad;    // Current particle velocity
    float       m_rotate;       // Rotate the particle the center
    float       m_size;         // Size of the particle
    float       m_age;
    float       m_life_time;
    float       m_distancia;

	TParticula();
    ~TParticula();

    void init(glm::vec3);
};

class TMotor{
private:
    glm::vec3 m_centro;
    vector<TParticula> m_particulas;
	glm::vec3 m_fuerza;
public:
    TMotor(glm::vec3, float, int);
    TMotor();
    ~TMotor();

    void update(float);
    void render(glm::vec3, int);
    unsigned size();
};

#endif