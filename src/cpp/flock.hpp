#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>

#include "prey.hpp"
#include "predator.hpp"

#include "SFML/Window.hpp"

class Flock{
public:
  std::size_t size() const{
    return preys.size() + predators.size();
  }

  void addPrey(Prey* prey){
    preys.push_back(prey);
  };

  void addPredator(Predator* predator){
    predators.push_back(predator);
  }

  /**
   * Computes the forces to be applied to each boid, and applies these. Dead
   * boids are removed.
   * @param width Screen width (number of pixels)
   * @param height Screen height (number of pixels.)
   */
    void step(int width, int height);

  /**
   * Draw all boids at their current positions.
   * @param window The SFML window onto which to draw the boids.
   */
    void draw(sf::RenderWindow& window);

private:
  std::vector<Prey*> preys;
  std::vector<Predator*> predators;
};

#endif // FLOCK_HPP
