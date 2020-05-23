#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"

Flock::~Flock(){
    for(auto ptr: preys)
        delete ptr;
    for(auto ptr: predators)
        delete ptr;
}

std::size_t Flock::size(){
    return preys.size() + predators.size();
}

void Flock::addPrey(Prey* prey){
    preys.push_back(prey);
    boids.push_back(static_cast<Boid*>(prey));
}

void Flock::addPredator(Predator* predator){
    predators.push_back(predator);
    boids.push_back(static_cast<Boid*>(predator));
}

void Flock::step(int width, int height) {
  // Loop through all Boids, compute forces for each
  for (auto prey : preys) {
    prey->computeForce(preys, predators);
  }
  for (auto predator : predators) {
    predator->computeForce(preys, predators);
  }

  // Loop through all, update using acceleration and eliminate killed prey
  for (auto prey : preys) {
    prey->step();
  }
  for (auto predator : predators) {
    predator->step();
  }
}

void Flock::draw(sf::RenderWindow &window){
    for(auto boid : boids)
        boid->draw(window);
}
