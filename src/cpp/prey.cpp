#include "prey.hpp"
#include "boid.hpp"
#include "predator.hpp"
#include "flock.hpp"

#include "SFML/Graphics.hpp"

Prey::Prey(Vec2 x0, Vec2 v0, double max_speed, double _separation_coeff)
: Boid(x0, v0, max_speed), separation_coeff(_separation_coeff){
    color = sf::Color::Green;
}

Vec2 Prey::separation(std::vector<Prey*>& preys){
    if(preys.size() == 0) return Vec2();
    Vec2 sum = Vec2();
    for(auto prey : preys){
        Vec2 diff = pos - prey->pos;
        double distance = pos.distanceSquared(prey->pos);
        sum += diff/(distance); // Weigh close boids more
    }
    sum /= (double)preys.size();
    return sum;
}

Vec2 Prey::alignment(std::vector<Prey*>& preys){
    if(preys.size() == 0) return Vec2();
    Vec2 sum = Vec2();
    for (auto prey : preys){
        sum += prey->vel;
    }
    sum /= (double)preys.size();
    return sum;
}

Vec2 Prey::cohesion(std::vector<Prey*>& preys){
    if (preys.size() == 0)
        return Vec2();

    Vec2 sum = Vec2();
    for (auto prey : preys) {
        sum += prey->pos;
    }
    sum /= (double)preys.size();
    return sum;
}

Vec2 Prey::centerPull(int width, int height){
    Vec2 center = Vec2((double)width/2, (double)height/2);
    Vec2 diff = pos - center;
    if (diff.lengthSquared() < width) return Vec2();
    return -k*diff;
}


void Prey::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators, int width, int height){
    findNearestNeighbors(preys, view_distance);
    acc = Vec2();

    force_separation  = separation(neighbors);
    force_alignment   = alignment(neighbors);
    force_cohesion    = cohesion(neighbors);
    force_center_pull = centerPull(width, height);
    acc += separation_coeff * force_separation;
    acc += alignment_coeff  * force_alignment;
    acc += cohesion_coeff   * force_cohesion;
    acc += force_center_pull;
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
