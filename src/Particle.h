#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <iostream>
class Particle{
public:
    int m_x;
    int m_y;
public:
    Particle();
    virtual ~Particle();
    void update(int xspeed, int yspeed);
};

#endif
