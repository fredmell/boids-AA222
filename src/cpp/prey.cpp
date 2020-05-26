#include "prey.hpp"
#include "boid.hpp"
#include "predator.hpp"

#include "SFML/Graphics.hpp"

Prey::Prey(Vec2 x0, Vec2 v0,
           double maxSpeed,
           double separationCoeff,
           double alignmentCoeff,
           double cohesionCoeff)
: Boid(x0, v0, maxSpeed), separationCoeff(separationCoeff), alignmentCoeff(alignmentCoeff), cohesionCoeff(cohesionCoeff){
    color = sf::Color::Green;
}

Vec2 Prey::Separation(std::vector<Prey*>& preys){
    double sepDistance = 10000;
    Vec2 sum = Vec2();
    unsigned int count = 0;
    for(auto prey : preys){
        double distance = pos.distanceSquared(prey->pos);
        if (distance > 0 and distance < sepDistance) {
            Vec2 diff = pos - prey->pos;
            sum += diff/(distance); // Weigh close boids more
            count++;
        }
    }
    if (count==0) return Vec2();
    sum /= (double)count;
    return sum;
}

Vec2 Prey::Alignment(std::vector<Prey*>& preys){
    double viewDistance = 10000;
    unsigned int count = 0;
    Vec2 sum = Vec2();
    for (auto prey : preys){
        double distance = pos.distanceSquared(prey->pos);
        if (distance > 0 and distance < viewDistance) {
            sum += prey->vel;
            count++;
        }
    }
    if(count == 0) return Vec2();
    sum /= (double)count;
    return sum;
}

Vec2 Prey::Cohesion(std::vector<Prey*>& preys){
    double viewDistance = 10000;
    unsigned int count = 0;
    Vec2 sum = Vec2();
    for(auto prey : preys){
        double distance = pos.distanceSquared(prey->pos);
        if (distance > 0 and distance < viewDistance){
            sum += prey->pos;
            count++;
        }
    }
    if (count == 0) return Vec2();
    sum /= (double)count;
    return sum;
}

Vec2 Prey::CenterPull(int width, int height){
    Vec2 center = Vec2((double)width/2, (double)height/2);
    Vec2 diff = pos - center;
    if (diff.lengthSquared() < (double)width) return Vec2();
    return -k*diff;
}


void Prey::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators, int width, int height){
    acc = Vec2();
    acc += separationCoeff * Separation(preys);
    acc += alignmentCoeff  * Alignment(preys);
    acc += cohesionCoeff   * Cohesion(preys);
    acc += CenterPull(width, height);
}
