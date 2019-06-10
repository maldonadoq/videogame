#include "../inc/modelo.h"

TModelo::TModelo(){

}

TModelo::TModelo(int _type, std::string _filename, std::string _textures, int _BGR_EXT, int _RGB){
	std::ifstream file(_filename);

	m_texture = TextureManager::Inst()->LoadTexture(_textures.c_str(),  _BGR_EXT, _RGB);

	if(file.bad()){
		std::cout << "Error: El archivo no puede abrirse!\n";
		return;
	}

	m_type = _type;

	std::string cabezera;
	std::string svertice;

	glm::vec3 gvertice;
	glm::vec2 guv;
	glm::vec3 gnorma;

	unsigned i;
	
	unsigned iv;
	unsigned iuv;
	unsigned inorma;

	float tmin[3] = {9999, 9999, 9999};
	float tmax[3] = {-9999, -9999, -9999};

	while(true){
		file >> cabezera;
		// std::cout << cabezera << " ";

		if(file.eof())
			break;

		if(cabezera == "v"){
			file >> gvertice.x >> gvertice.y >> gvertice.z;
			m_vertice.push_back(gvertice);

			for(i=0; i<3; i++){
				if(gvertice[i] < tmin[i])
					tmin[i] = gvertice[i];
				if(gvertice[i] > tmax[i])
					tmax[i] = gvertice[i];
			}
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
			for(i=0; i<m_type; i++){
				file >> svertice;

				sscanf(svertice.c_str(), "%d/%d/%d", &iv, &iuv, &inorma);
				m_vertice_idx.push_back(iv-1);
				m_uv_idx.push_back(iuv-1);
				m_normal_idx.push_back(inorma-1);
			}
		}
	}

	for(unsigned i=0; i<m_vertice.size(); i++){
		m_vertice[i].y -= (tmin[1] + (tmax[1] - tmin[1])/2);
	}

	this->m_dim = 0.0f;
	for(i=0; i<3; i++){
		m_dim += (tmax[i] - tmin[i]);
	}

	m_dim = (float)m_dim/6;
	// std::cout << "dim: " << m_dim << "\n";
}

void TModelo::dibujar() const{

	glm::vec3 tvertice;
	glm::vec3 tnormal;
	glm::vec2 ttextures;

	// glDisable(GL_CULL_FACE);
	
	glBindTexture(GL_TEXTURE_2D, m_texture);

	if(m_type == 3)	glBegin(GL_TRIANGLES);
	if(m_type == 4)	glBegin(GL_QUADS);

		for(unsigned i=0; i<m_vertice_idx.size(); i++){
			tvertice = m_vertice[m_vertice_idx[i]];
			tnormal  = m_normal[m_normal_idx[i]];
			ttextures = m_uv[m_uv_idx[i]];

			glTexCoord2f(ttextures.x, ttextures.y);
			glNormal3f(tnormal.x, tnormal.y, tnormal.z);
			glVertex3f(tvertice.x, tvertice.y, tvertice.z);
		}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}