#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Predator;

class Prey: public Boid {
public:
    Prey(Vec2 x0, Vec2 v0, double maxSpeed = 1.0, double separationCoeff = 1.0);

    Vec2 Separation(std::vector<Prey*>&);
    Vec2 Alignment(std::vector<Prey*>&);
    Vec2 Cohesion(std::vector<Prey*>&);
    Vec2 CenterPull(int width, int height);
    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&, int, int);

    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&);
    void setFlock(Flock*) override;
    void findNearestNeighbors(const std::vector<Prey*>&, double max_distance);

    int id_prey = -1;

    double sepCoeff;
    double separationCoeff;
    const double alignmentCoeff = 1.0;
    const double cohesionCoeff = 1.0;
    const double view_distance = 200;
    double k = 0.0000001; // Spring constant

    std::vector<Prey*> neighbors;
};

#endif // PREY_HPP
