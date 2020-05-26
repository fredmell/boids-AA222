#include <algorithm>

#include "predator.hpp"
#include "boid.hpp"
#include "prey.hpp"
#include "flock.hpp"

#include "SFML/Graphics.hpp"

Predator::Predator(Vec2 x0, Vec2 v0, double maxSpeed, double killRange)
: Boid(x0, v0, 3), range(killRange) {
    color = sf::Color::Red;
}

Vec2 Predator::hunt(std::vector<Prey*>& preys){

    // Handle zero prey case
    if(preys.size() == 0) return Vec2();
    // Find nearest prey
    auto minElement = std::min_element(preys.begin(),
                                       preys.end(),
                                       [this](Prey* prey1, Prey* prey2){
                                           auto d1 = this->pos.distanceSquared(prey1->pos);
                                           auto d2 = this->pos.distanceSquared(prey2->pos);
                                           return d1 < d2;
                                       });
    Prey* closest = *minElement;

    if(pos.distance(closest->pos) < range){
        closest->kill();
    }

    // Return direction towards nearest prey
    Vec2 direction = (closest->pos - pos);
    direction.normalize();
    return 2*direction;
}

Vec2 Predator::avoidFlock(std::vector<Prey*>& preys){
    return Vec2();
}

Vec2 Predator::Separation(std::vector<Predator*>& predators){
    double sepDistance = 200;
    Vec2 sum = Vec2();
    unsigned int count = 0;
    for(auto predator : predators){
        double distance = pos.distanceSquared(predator->pos);
        if (distance > 0 and distance < sepDistance) {
            Vec2 diff = pos - predator->pos;
            sum += diff/(distance); // Weigh close boids more
            count++;
        }
    }
    if (count==0) return Vec2();
    sum /= (double)count;
    return sum;
}

void Predator::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators){
    acc = Vec2();
    if(preys.size() == 0) return;
    acc += hunt(preys);
    acc += avoidFlock(preys);
    acc += separationCoeff * Separation(predators);
}

void Predator::setFlock(Flock* _flock){
    flock = _flock;
    id_boid = flock->boids.size() - 1;
    id_predator = flock->predators.size() - 1;
}
