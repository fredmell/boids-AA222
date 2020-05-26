#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>

#include "boid.hpp"
#include "prey.hpp"
#include "predator.hpp"

#include "SFML/Window.hpp"

class Flock{
public:
    Flock();
    virtual ~Flock();
    std::size_t size();

    void addPrey(Prey* prey);
    void addPredator(Predator* predator);

    /**
     * Computes the forces to be applied to each boid, and applies these. Dead
     * boids are removed.
     * @param width Screen width
     * @param height Screen height
     */
    void step(int width, int height);

    /**
     * Draw all boids at their current positions.
     * @param window The SFML window onto which to draw the boids.
     */
    //void updateShapes();
    void removeDead();
    void addCausalty(Boid*);

    std::vector<Prey*> preys;
    std::vector<Predator*> predators;
    // Contains both preys and predators for easy iteration
    std::vector<Boid*> boids;

    size_t num_dead = 0;
    // 512 just in case. Might segfault:P
    Boid* boid_bodies[512];

};

#endif // FLOCK_HPP
