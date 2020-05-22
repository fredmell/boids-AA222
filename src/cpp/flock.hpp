#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>

#include "boid.hpp"
#include "prey.hpp"
#include "predator.hpp"

#include "SFML/Window.hpp"

class Flock{
public:
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
   void draw(sf::RenderWindow& window);

   std::vector<Prey*> preys;
   std::vector<Predator*> predators;
};

#endif // FLOCK_HPP
