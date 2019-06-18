#include "../inc/hydra.h"

GLfloat hno_emit[] = {1.0, 1.0, 1.0, 1.0};

THydra::THydra(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = 5;
    this->m_modelo = _model;
    this->m_direccion = 10.0f*RandomVect();
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion.y += (m_modelo->m_dim/2.0f);
    this->m_split = false;
}

void THydra::mover(glm::vec3 _dim, glm::vec3 _centro, float _dt){
    // std::cout << "ovni moviendose\n";
    glm::vec3 _pos;
    if(!m_split){
        _pos = m_posicion + (m_direccion*_dt);
        if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
            m_posicion = _pos;
        }
        else{
            restart();
        }
    }
    else{
        for(unsigned i=0; i<m_thydra.size(); i++){
            _pos = m_thydra[i].m_pos + (m_thydra[i].m_dir*_dt);
            if(cuarto_colision(_dim - glm::vec3(m_tmodel.m_dim, m_tmodel.m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
                m_thydra[i].m_pos = _pos;
            }
            else{
                m_thydra[i].m_dir = 10.0f*RandomVect();
            }
        }
    }
}

void THydra::disparar(glm::vec3 _pos, float _dt){
    if(m_tiempo_disparar > 2.5f){
        glm::vec3 _dir;
        TBala tb;
        if(!m_split){
            _dir = glm::normalize(_pos - m_posicion)*_dt*50.0f;
            tb = {0.2f, m_posicion, _dir};

            m_balas.push_back(tb);
        }
        else{
            for(int i=0; i<(int)m_thydra.size(); i++){
                _dir = glm::normalize(_pos - m_thydra[i].m_pos)*_dt*50.0f;
                tb = {0.2f, m_thydra[i].m_pos, _dir};
                m_balas.push_back(tb);
            }
        }
        m_tiempo_disparar = 0.0f;
    }
}

int THydra::colision(glm::vec3 _pos, float _r){
    int ty = -1;
    float dis;

    if(!m_split){
        dis = glm::distance(_pos, m_posicion);
        if(dis < (m_modelo->m_dim + _r)){
            ty = 1;
            m_vida--;

            if(m_vida <= 0){
                m_split = true;
                m_tmodel = m_modelo->get_small();

                m_posicion.y = 1;
                m_posicion.y += m_tmodel.m_dim/2.0f;

                m_thydra.push_back({m_posicion, 10.0f*RandomVect(), 5});
                m_thydra.push_back({m_posicion, 10.0f*RandomVect(), 5});
                // m_tmodel = *m_modelo;
            }
        }
    }
    else{
        for(int i=0; i<(int)m_thydra.size(); i++){
            dis = glm::distance(_pos, m_thydra[i].m_pos);
            if(dis < (m_tmodel.m_dim + _r)){
                ty = 1;
                m_thydra[i].m_vid--;

                if(m_thydra[i].m_vid <= 0){
                    m_thydra.erase(m_thydra.begin() + i);
                    i--;
                }
            }
        }

        if(m_thydra.size() == 0){
            ty = 2;
        }
    }

    return ty;
}

void THydra::dibujar(glm::vec3 _dim, glm::vec3 _centro, bool _col){    
    if(!m_split){
        TEnemigo::dibujar(_dim, _centro, _col);
    }
    else{
        dibujar_balas(_dim, _centro);
        float emit[]    = {0.0, 1.0, 0.0, 1.0};
        
        for(unsigned i=0; i<m_thydra.size(); i++){
            glPushMatrix();
                glTranslatef(m_thydra[i].m_pos.x, m_thydra[i].m_pos.y, m_thydra[i].m_pos.z);
                if(_col){
                    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
                        glColor3f(0,1,0);
                        glutWireSphere(m_tmodel.m_dim/2.0f, 8, 8);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, hno_emit);
                }
                m_tmodel.dibujar();
            glPopMatrix();
        }
    }
}