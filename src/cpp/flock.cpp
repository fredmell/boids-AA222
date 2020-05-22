#include "flock.hpp"


void Flock::step(int width, int height) {
  // Loop through all Boids, compute forces for each
  for (Prey &prey : preys) {
    prey.computeForce(prey, predators);
  }
  for (Predator &predator : predators) {
    predator.computeForce(preys);
  }

  // Loop through all, update using accelleration and eliminate killed prey
  for (Prey &prey : preys) {
    prey.step();
  }
  for (Predator &predator : preys) {
    predator.step();
  }
}

void Flock::draw(sf::RenderWindow &window){
  for (auto prey : preys) {
    prey->draw(window);
  }
  for (auto predator : predators) {
    predator->draw(window);
  }
}
