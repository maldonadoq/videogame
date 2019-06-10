#ifndef _MODELO_H_
#define _MODELO_H_

#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include "../inc/tmanager.h"

#include <glm/glm.hpp>
#include <GL/glut.h>

class TModelo{
private:
	int m_type;

	std::vector<glm::vec3> m_vertice;
	std::vector<glm::vec2> m_uv;
	std::vector<glm::vec3> m_normal;

	std::vector<unsigned> m_vertice_idx;
	std::vector<unsigned> m_uv_idx;
	std::vector<unsigned> m_normal_idx;

	int m_texture;
public:
	float m_dim;
	
	TModelo(int, std::string, std::string, int, int);
	TModelo();

	void dibujar() const;
	~TModelo();
};

#endif