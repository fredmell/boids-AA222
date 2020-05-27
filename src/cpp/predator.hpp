#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Prey;

class Predator: public Boid {
public:
  Predator(Vec2 x0, Vec2 v0, double maxSpeed = 1.1, double killRange = 4.0);

    Vec2 hunt(std::vector<Prey *> &);
    Vec2 avoidFlock(std::vector<Prey *> &);
    Vec2 Separation(std::vector<Predator *> &);

    void computeForce(std::vector<Prey *> &, std::vector<Predator *> &);
    void setFlock(Flock *) override;

    int id_prey = -1;
    int id_predator = -1;

    Prey* target;
    const double flee_distance = 80;
    const int flee_number = 3;

    double separationCoeff = 10.0;
    double alignmentCoeff = 1.0;
    double cohesionCoeff = 1.0;
    double k = 0.0000001; // Spring constant

    double range;
};

#endif // PREDATOR_HPP
