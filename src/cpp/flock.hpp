#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>

#include "boid.hpp"
#include "prey.hpp"
#include "predator.hpp"

#include "SFML/Window.hpp"

class Flock{
public:
    std::size_t size(){
        return this->_prey.size() + this->_predators.size();
    }

    void addPrey(Prey prey){
        this->_prey.push_back(prey);
    };

    void addPredator(Predator predator){
        this->_predators.push_back(predator);
    }

    /**
     * Computes the forces to be applied to each boid, and applies these. Dead
     * boids are removed.
     * @param width Screen width (number of pixels)
     * @param height Screen height (number of pixels.)
     */
    void step(int width, int height){
        // Loop through all Boids, compute forces for each
        for(Prey& prey : this->_prey){
            prey.computeForce(this->_prey, this->_predators);
        }
        for(Predator& predator : this->_predators){
            predator.computeForce(this->_prey, this->_predators);
        }

        // Loop through all, update using acceleration and eliminate killed prey
        for(Predator& predator : this->_prey){
            predator.step();
        }
        for(Prey& prey : this->_prey){
            bool alive = true;
            prey.step(alive);
        }
    }

    /**
     * Draw all boids at their current positions.
     * @param window The SFML window onto which to draw the boids.
     */
    void draw(sf::RenderWindow& window){
        for(Prey& prey : this->_prey){
            prey.draw(window);
        }
        for(Predator& predator : this->_predators){
            predator.draw(window);
        }
    }

private:
    std::vector<Boid*> boids;
};

#endif // FLOCK_HPP
