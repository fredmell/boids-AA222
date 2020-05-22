#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "boid.hpp"
#include "prey.hpp"
#include "vec2.hpp"

class Predator: public Boid {
public:
  Predator(Vec2 x0, Vec2 v0);

  void computeForce(std::vector<Prey*>&, std::vector<Predator*>&);
};

#endif // PREDATOR_HPP
