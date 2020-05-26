#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Predator;

class Prey: public Boid {
public:
    Prey(Vec2 x0, Vec2 v0,
         double maxSpeed = 1.0,
         double separationCoeff = 1.0,
         double alignmentCoeff = 1.0,
         double cohesionCoeff = 1.0);

    Vec2 Separation(std::vector<Prey*>&);
    Vec2 Alignment(std::vector<Prey*>&);
    Vec2 Cohesion(std::vector<Prey*>&);
    Vec2 CenterPull(int width, int height);
    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&, int, int);

    double separationCoeff;
    double alignmentCoeff;
    double cohesionCoeff;
    double k = 0.00001; // Spring constant
};

#endif // PREY_HPP
