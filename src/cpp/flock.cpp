#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"

std::size_t Flock::size(){
    return preys.size() + predators.size();
}

void Flock::addPrey(Prey* prey){
    preys.push_back( prey );
}

void Flock::addPredator(Predator* predator){
    predators.push_back( predator );
}

void Flock::step(int width, int height) {
  // Loop through all Boids, compute forces for each
  // for (auto prey : preys) {
  //   prey->computeForce(preys, predators);
  // }
  // for (auto predator : predators) {
  //   predator->computeForce(preys, predators);
  // }

  // Loop through all, update using acceleration and eliminate killed prey
  for (auto prey : preys) {
    prey->step();
  }
  for (auto predator : predators) {
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
