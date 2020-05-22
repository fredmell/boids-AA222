#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"

class Prey: public Boid {
  Prey(Vec2 x0, Vec2 v0) : Boid(x0, v0) {};
};

#endif // PREY_HPP
