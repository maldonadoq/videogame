#ifndef _UTILS_H_
#define _UTILS_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::to_string;

struct TLuz
{
	glm::vec4 m_position;

	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
};

struct TMaterial
{
	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
	float m_shininess;
};

void dibujar_luz(TLuz, float);
bool cuarto_colision(glm::vec3, glm::vec3, glm::vec3);
bool cuarto_colision(glm::vec3, glm::vec3, glm::vec3, glm::vec2 &);
string vec3_to_str(glm::vec3);

#define PI 3.14159265
void draw_circle(float, int);
void print_vec3(glm::vec3);
void Font(string, float, float);

#endif