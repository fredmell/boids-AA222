#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Predator;

class Prey: public Boid {
public:
    Prey(Vec2 x0, Vec2 v0, double maxSpeed = 1.0);

    

    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&);
};

#endif // PREY_HPP
