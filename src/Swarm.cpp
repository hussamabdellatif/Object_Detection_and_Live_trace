#include "Swarm.h"

Swarm::Swarm(){
    m_particle = new Particle[NPARTICLES];
}

Swarm::~Swarm(){
    delete[] m_particle;
}

void Swarm::update(int x, int y){
    for(int i=0;i<Swarm::NPARTICLES;i++){
        m_particle[i].update(x,y);
    }
}
