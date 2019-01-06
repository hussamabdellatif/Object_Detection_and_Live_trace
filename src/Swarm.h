
#ifndef SWARM_H_
#define SWARM_H_
#include "Particle.h"

class Swarm{
public:
    const static int NPARTICLES = 20000;
private:
    Particle *m_particle;
public:
    Swarm();
    virtual ~Swarm();
    Particle *getParticles(){return m_particle;};
    void update(int x,int y);
};

#endif
