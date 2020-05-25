#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Predator;

class Prey: public Boid {
public:
    Prey(Vec2 x0, Vec2 v0, double maxSpeed = 1.0, double sepCoeff = 1.0);

    Vec2 Separation(std::vector<Prey*>&);
    Vec2 Alignment(std::vector<Prey*>&);
    Vec2 Cohesion(std::vector<Prey*>&);

    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&);

    double sepCoeff;
};

#endif // PREY_HPP
