#include <algorithm>

#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "boid.hpp"

Flock::Flock(){
}

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

  remove_dead();

  // Update velocity using acceleration, update position using velocity
  for (auto prey : preys) {
    prey->step();
  }
  for (auto predator : predators) {
    predator->step();
  }
}

void Flock::remove_dead(){
    // Remove dead boids by freeing the memory, setting the ptr to nullptr and
    // removing nullptrs.
    for (auto& prey : preys){
        if (not prey->alive){
            delete prey;
            prey = nullptr;
        }
    }
    preys.erase(std::remove(preys.begin(), preys.end(), nullptr), preys.end());
}
