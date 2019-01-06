#include "Particle.h"
#include "Screen.h"
#include <stdlib.h>

Particle::Particle(){
    m_x = (int)(Screen::SCREEN_WIDTH/2) + (((2.0 *rand())/RAND_MAX) -1);
    m_y = (int)(Screen::SCREEN_HEIGHT/2) + (((2.0 *rand())/RAND_MAX) -1);
    //std::cout<<((2.0 *rand())/RAND_MAX) -1<<std::endl;
}

Particle::~Particle(){

}

void Particle::update(int xspeed, int yspeed){
    //const double xspeed = 0.01*(((2.0*rand())/RAND_MAX)-1);
    //const double yspeed = 0.01*(((2.0*rand())/RAND_MAX)-1);
    m_x += xspeed;
    m_y += yspeed;
}
