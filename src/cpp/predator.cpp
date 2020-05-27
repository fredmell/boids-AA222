#include <algorithm>

#include "predator.hpp"
#include "boid.hpp"
#include "prey.hpp"
#include "flock.hpp"

#include "SFML/Graphics.hpp"

Predator::Predator(Vec2 x0, Vec2 v0, double max_speed, double kill_range)
: Boid(x0, v0, max_speed), range(kill_range) {
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
    target = *minElement;

    if(pos.distance(target->pos) < range){
        target->kill();
    }

    // Return direction towards nearest prey
    Vec2 direction = (target->pos - pos);
    direction.normalize();
    return direction;
}

Vec2 Predator::avoidFlock(std::vector<Prey*>& preys){
    Vec2 force;
    int num_close = 0;
    for (auto prey : target->neighbors){
        if( pos.distance(prey->pos) < flee_distance ) num_close++;
    }
    if (num_close > flee_number){
        force -= target->pos;
    }
    return force;
}

Vec2 Predator::Separation(std::vector<Predator*>& predators){
    double sepDistance = 10000;
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
