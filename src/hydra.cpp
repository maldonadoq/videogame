#include "../inc/hydra.h"

float hno_emit[]    = {1.0, 1.0, 1.0, 1.0};

THydra::THydra(glm::vec3 _pos, TModelo *_model): TEnemigo(_pos){
    this->m_vida = ehydra;
    this->m_modelo = _model;
    this->m_direccion = 10.0f*RandomVect();
    this->m_tiempo_disparar = 0.0f;
    this->m_posicion.y += (m_modelo->m_dim/2.0f);
    this->m_split = false;

    this->m_color = glm::vec3(1.0f,1.0f,0.0f);
}

void THydra::mover(glm::vec3 _jug, glm::vec3 _dim, glm::vec3 _centro, float _dt){
    // std::cout << "ovni moviendose\n";
    glm::vec3 _pos;
    if(!m_split){
        _pos = m_posicion + (10.0f*m_direccion*_dt);
        if(cuarto_colision(_dim - glm::vec3(m_modelo->m_dim, m_modelo->m_dim/2.0f, m_modelo->m_dim), _centro, _pos)){
            m_posicion = _pos;
            disparar(_jug, _dt);
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
        disparar(_jug, _dt);
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
        if(dis < (m_modelo->m_dim/2.0f + _r)){
            ty = 1;
            m_vida--;

            if(m_vida <= 0){
                m_split = true;
                m_tmodel = m_modelo->get_small();

                m_posicion.y = 1;
                m_posicion.y += m_tmodel.m_dim/2.0f;

                m_thydra.push_back({m_posicion, 10.0f*RandomVect(), ehydra});
                m_thydra.push_back({m_posicion, 10.0f*RandomVect(), ehydra});
                // m_tmodel = *m_modelo;

                ty = 3;
            }
        }
    }
    else{
        for(int i=0; i<(int)m_thydra.size(); i++){
            dis = glm::distance(_pos, m_thydra[i].m_pos);
            if(dis < (m_tmodel.m_dim/2.0f + _r)){
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

void THydra::barra_vida(glm::vec3 _jug){
    if(!m_split){
        TEnemigo::barra_vida(_jug);
    }
    else{
        glm::vec3 tmp;
        float angley;
        for(unsigned i=0; i<m_thydra.size(); i++){
            tmp = glm::normalize((_jug - glm::vec3(m_thydra[i].m_pos.x, _jug.y, m_thydra[i].m_pos.z)));
            angley = glm::orientedAngle(glm::vec2(tmp.x, tmp.z), glm::vec2(m_tmodel.m_dir.x, m_tmodel.m_dir.z))*180/PI;

            glPushMatrix();
                glTranslatef(m_thydra[i].m_pos.x, m_thydra[i].m_pos.y + (m_tmodel.m_dim/2.0f) + 2.0f, m_thydra[i].m_pos.z);
                glRotatef(angley, 0.0f, 1.0f, 0.0f);

                float emit[]    = {1.0f,0.0f,0.0f, 1.0f};
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
                glColor3f(1.0f,0.0f,0.0f);
                    glBegin(GL_QUADS);
                        // Front face  (z = 1.0f)
                        glVertex3f( 2.0f,  0.25f, 0.0f);
                        glVertex3f(-2.0f,  0.25f, 0.0f);
                        glVertex3f(-2.0f, -0.25f, 0.0f);
                        glVertex3f( 2.0f, -0.25f, 0.0f);
                    glEnd();
                
                float l = (4/(float)ehydra)*m_thydra[i].m_vid;

                emit[0] = 0.0f;
                emit[1] = 1.0f;
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
                glColor3f(0.0f,1.0f,0.0f);
                    glBegin(GL_QUADS);
                        // Front face  (z = 1.0f)
                        glVertex3f(-2.0+ l,  0.25f, 0.1f);
                        glVertex3f(-2.0f,  0.25f, 0.1f);
                        glVertex3f(-2.0f, -0.25f, 0.1f);
                        glVertex3f(-2.0 + l, -0.25f, 0.1f);
                    glEnd();

                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, hno_emit);
            glPopMatrix();
        }
    }

}

float THydra::get_size(float _size){
    return (_size/(float)ehydra)*m_vida;
}