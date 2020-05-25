#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Prey;

class Predator: public Boid {
public:
  Predator(Vec2 x0, Vec2 v0, double maxSpeed = 1.1, double killRange = 4.0);

  Vec2 hunt(std::vector<Prey*>&);
  Vec2 avoidFlock(std::vector<Prey*>&);
  Vec2 Separation(std::vector<Predator*>&);

  void computeForce(std::vector<Prey*>&, std::vector<Predator*>&);

  double range;
};

#endif // PREDATOR_HPP
