#include <algorithm>

#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "boid.hpp"

Flock::Flock(double width, double height){
    Vec2 center(width/2, height/2);
    double size = 10*width;
    qtree = new QuadTree<Boid*>(0, Rectangle(center, size));
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
    prey->setFlock(this);
}

void Flock::addPredator(Predator* predator){
    predators.push_back(predator);
    boids.push_back(static_cast<Boid*>(predator));
    predator->setFlock(this);
}

void Flock::step(int width, int height, unsigned t) {
    //qtree->clear();
    //for(auto boid : boids){
    //     qtree->insert(boid);
    //}

    for (auto prey : preys) {
        prey->computeForce(preys, predators, width, height);
    }
    for (auto predator : predators) {
        predator->computeForce(preys, predators);
    }

    removeDead();

    for (auto prey : preys) {
        prey->step();
    }
    for (auto predator : predators) {
        predator->step();
    }
}

void Flock::addCausalty(Prey* boid){
    boid_bodies[num_dead++] = boid;
}

void Flock::removeDead(){
    if (num_dead <= 0) return;

    // maybe not. Can instead have a counter num_dead and cease iteration when all have been found
    Prey* boid;
    int i, j;
    while(num_dead > 0){
        // Get the dead boid
        i = --num_dead;
        boid = boid_bodies[i];

        // Get the indices of the boids and preys vectors
        i = boid->id_boid;
        j = boid->id_prey;

        // Override the place with the back
        boids[i] = std::move(boids.back());
        preys[j] = std::move(preys.back());

        // delete the now empty back
        boids.pop_back();
        preys.pop_back();

        // Update the moved boid's indices
        boids[i]->id_boid = i;
        preys[j]->id_prey = j;

        delete boid;
    }
}
