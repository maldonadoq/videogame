#ifndef _BOTON_H_
#define _BOTON_H_

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "utils.h"

using std::string;

class TBoton{
private:
	string text;
	glm::vec2 center;
public:
	TBoton();
	TBoton(glm::vec2, string);
	~TBoton();

	void dibujar(glm::vec4, glm::vec2);
};

#endif