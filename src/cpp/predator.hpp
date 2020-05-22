#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Predator: public Boid {
public:
  Predator(Vec2 x0, Vec2 v0);
};

#endif // PREDATOR_HPP
