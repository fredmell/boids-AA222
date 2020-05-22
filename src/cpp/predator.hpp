#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "boid.hpp"

class Predator: public Boid {
public:
  Prey(Vec2 x0, Vec2 v0); 
};

#endif // PREDATOR_HPP
