#include <algorithm>

#include "predator.hpp"
#include "boid.hpp"
#include "prey.hpp"

#include "SFML/Graphics.hpp"

Predator::Predator(Vec2 x0, Vec2 v0, double maxSpeed, double killRange)
: Boid(x0, v0, maxSpeed), range(killRange) {
    color = sf::Color::Red;
}

Vec2 Predator::hunt(std::vector<Prey*>& preys){

    // Handle zero prey case
    if(preys.size() == 0) return Vec2();
    // Find nearest prey
    auto minElement = std::min_element(preys.begin(),
                                       preys.end(),
                                       [this](Prey* prey1, Prey* prey2){
                                           auto d1 = this->pos.distance(prey1->pos);
                                           auto d2 = this->pos.distance(prey2->pos);
                                           return d1 < d2;
                                       });
    Prey* closest = *minElement;

    if(pos.distance(closest->pos) < range){
        closest->alive = false;
    }

    // Return direction towards nearest prey
    Vec2 direction = (closest->pos - pos);
    direction.normalize();
    return direction;
}

Vec2 Predator::avoidFlock(std::vector<Prey*>& preys){
    return Vec2();
}

void Predator::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators){
    acc = Vec2();
    if(preys.size() == 0) return;
    acc += hunt(preys);
    acc += avoidFlock(preys);
}
