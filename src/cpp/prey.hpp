#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Prey: public Boid {
public:
  Prey(Vec2 x0, Vec2 v0);
};

#endif // PREY_HPP
