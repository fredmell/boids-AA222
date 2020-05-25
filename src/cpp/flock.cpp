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
  for (auto prey : preys) {
    prey->computeForce(preys, predators);
  }
  for (auto predator : predators) {
    predator->computeForce(preys, predators);
  }

  remove_dead();

  for (auto prey : preys) {
    prey->step();
  }
  for (auto predator : predators) {
    predator->step();
  }
}

void Flock::remove_dead(){
    bool causalty = false;
    for (auto& prey : preys){
        if (not prey->alive){
          boids.erase(std::remove(boids.begin(), boids.end(), prey),
                      boids.end());
          delete prey;
          prey = nullptr;
          causalty = true;
        }
    }
    if(not causalty) return;

    preys.erase(std::remove(preys.begin(), preys.end(), nullptr), preys.end());
}
