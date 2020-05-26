#include "prey.hpp"
#include "boid.hpp"
#include "predator.hpp"
#include "flock.hpp"

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
    Vec2 sum = Vec2();
    unsigned int count = 0;
    for(auto prey : preys){
        Vec2 diff = pos - prey->pos;
        double distance = pos.distanceSquared(prey->pos);
        sum += diff/(distance); // Weigh close boids more
        count++;
    }
    if (count==0) return Vec2();
    sum /= (double)count;
    return sum;
}

Vec2 Prey::Alignment(std::vector<Prey*>& preys){
    unsigned int count = 0;
    Vec2 sum = Vec2();
    for (auto prey : preys){
        sum += prey->vel;
        count++;
    }
    if(count == 0) return Vec2();
    sum /= (double)count;
    return sum;
}

Vec2 Prey::Cohesion(std::vector<Prey*>& preys){
    unsigned int count = 0;
    Vec2 sum = Vec2();
    for(auto prey : preys){
        sum += prey->pos;
        count++;
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
    findNearestNeighbors(preys, view_distance);
    acc = Vec2();
    acc += separationCoeff * Separation(neighbors);
    acc += alignmentCoeff  * Alignment(neighbors);
    acc += cohesionCoeff   * Cohesion(neighbors);
    acc += CenterPull(width, height);
}

void Prey::setFlock(Flock* _flock){
    flock = _flock;
    id_boid = flock->boids.size() - 1;
    id_prey = flock->preys.size() - 1;
}

void Prey::findNearestNeighbors(const std::vector<Prey*>& preys, double max_distance){
    double distancesq;
    neighbors.clear();
    for(auto prey: preys){
        distancesq = pos.distanceSquared(prey->pos);
        if(distancesq > 0 and distancesq < max_distance){
            neighbors.push_back(prey);
        }
    }
}
