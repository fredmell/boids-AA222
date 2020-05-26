#ifndef PREY_HPP
#define PREY_HPP

#include "boid.hpp"
#include "vec2.hpp"

class Predator;

class Prey: public Boid {
public:
    Prey(Vec2 x0, Vec2 v0, double max_speed = 1.0, double _separation_coeff = 1.0, double _alignment_coeff = 1.0, double _cohesion_coeff = 0.2);

    Vec2 separation(std::vector<Prey*>&);
    Vec2 alignment(std::vector<Prey*>&);
    Vec2 cohesion(std::vector<Prey*>&);
    Vec2 centerPull(int width, int height);
    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&, int, int);

    void computeForce(std::vector<Prey*>&, std::vector<Predator*>&);
    void setFlock(Flock*) override;
    void findNearestNeighbors(const std::vector<Prey*>&, double max_distance);

    void drawForces(sf::Vertex*);

    int id_prey = -1;

    const double separation_coeff;
    const double alignment_coeff;
    const double cohesion_coeff;
    const double view_distance = 200;
    double k = 0.0000001; // Spring constant

    Vec2 force_separation;
    Vec2 force_alignment;
    Vec2 force_cohesion;
    Vec2 force_center_pull;

    std::vector<Prey*> neighbors;
};

#endif // PREY_HPP
