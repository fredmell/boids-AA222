#include "flock.hpp"


void Flock::step(int width, int height) {
  // Loop through all Boids, compute forces for each
  for (auto prey : preys) {
    prey->computeForce(prey, predators);
  }
  for (auto predator : predators) {
    predator->computeForce(preys);
  }

  // Loop through all, update using accelleration and eliminate killed prey
  for (auto prey : preys) {
    prey->step();
  }
  for (auto predator : preys) {
    predator->step();
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
