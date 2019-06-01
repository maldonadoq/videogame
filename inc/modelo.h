#ifndef _MODELO_H_
#define _MODELO_H_

#include <vector>
#include <fstream>
#include <map>
#include <iostream>

#include <glm/glm.hpp>
#include <GL/glut.h>

class TModelo{
private:
	std::vector<glm::vec3> m_vertice;
	std::vector<glm::vec2> m_uv;
	std::vector<glm::vec3> m_normal;

	std::vector<unsigned> m_vertice_idx;
	std::vector<unsigned> m_uv_idx;
	std::vector<unsigned> m_normal_idx;	
public:
	TModelo(std::string);
	TModelo();

	void dibujar() const;
	~TModelo();
};

#endif