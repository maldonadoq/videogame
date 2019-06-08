#include "../inc/modelo.h"

TModelo::TModelo(){

}

TModelo::TModelo(std::string _filename, std::string _textures){
	std::ifstream file(_filename);

	m_texture = TextureManager::Inst()->LoadTexture(_textures.c_str(),  GL_BGR_EXT, GL_RGB);

	if(file.bad()){
		std::cout << "Error: El archivo no puede abrirse!\n";
		return;
	}

	std::string cabezera;
	std::string svertice;

	glm::vec3 gvertice;
	glm::vec2 guv;
	glm::vec3 gnorma;

	unsigned i;
	
	unsigned iv;
	unsigned iuv;
	unsigned inorma;

	while(true){
		file >> cabezera;
		// std::cout << cabezera << " ";

		if(file.eof())
			break;

		if(cabezera == "v"){
			file >> gvertice.x >> gvertice.y >> gvertice.z;
			m_vertice.push_back(gvertice);
		}
		else if(cabezera == "vt"){
			file >> guv.x >> guv.y;
			m_uv.push_back(guv);
		}
		else if(cabezera == "vn"){
			file >> gnorma.x >> gnorma.y >> gnorma.z;
			m_normal.push_back(gnorma);
		}
		else if(cabezera == "f"){
			for(i=0; i<4; i++){
				file >> svertice;

				sscanf(svertice.c_str(), "%d/%d/%d", &iv, &iuv, &inorma);
				m_vertice_idx.push_back(iv-1);
				m_uv_idx.push_back(iuv-1);
				m_normal_idx.push_back(inorma-1);
			}
		}
	}

	std::cout << "Modelo " << _filename << " cargado!\n";
	std::cout << "Vertice: " << m_vertice_idx.size() << "\n";
	std::cout << "Normal: " << m_normal_idx.size() << "\n";
	std::cout << "Textures: " << m_uv_idx.size() << "\n";
}

void TModelo::dibujar() const{

	glm::vec3 tvertice;
	glm::vec3 tnormal;
	glm::vec2 ttextures;

	// glDisable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
		for(unsigned i=0; i<m_vertice_idx.size(); i++){
			tvertice = m_vertice[m_vertice_idx[i]];
			tnormal  = m_normal[m_normal_idx[i]];
			ttextures = m_uv[m_uv_idx[i]];

			glTexCoord2f(ttextures.x, ttextures.y);
			glNormal3f(tnormal.x, tnormal.y, tnormal.z);
			glVertex3f(tvertice.x, tvertice.y, tvertice.z);
		}
	glEnd();
}