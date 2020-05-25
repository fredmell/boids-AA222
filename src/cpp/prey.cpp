#include "prey.hpp"
#include "boid.hpp"
#include "predator.hpp"

#include "SFML/Graphics.hpp"

Prey::Prey(Vec2 x0, Vec2 v0, double maxSpeed, double sepCoeff)
: Boid(x0, v0, maxSpeed), sepCoeff(sepCoeff){
    color = sf::Color::Green;
}

Vec2 Prey::Separation(std::vector<Prey*>& preys){
    double sepDistance = 30;
    Vec2 sum = Vec2();
    for(auto prey : preys){
        double distance = pos.distance(prey->pos);
        if (distance > 0 and distance < sepDistance) {
            Vec2 diff = pos - prey->pos;
            sum += diff/(distance*distance); // Weigh close boids more
        }
    }
    sum.normalize();
    return sum;
}

Vec2 Prey::Alignment(std::vector<Prey*>& preys){
    double viewDistance = 200;
    Vec2 sum = Vec2();
    for (auto prey : preys){
        double distance = pos.distance(prey->pos);
        if (distance > 0 and distance < viewDistance) {
            sum += prey->vel;
        }
    }
    sum.normalize();
    return sum;
}

Vec2 Prey::Cohesion(std::vector<Prey*>& preys){
    double viewDistance = 200;
    unsigned int count = 0;
    Vec2 sum = Vec2();
    for(auto prey : preys){
        double distance = pos.distance(prey->pos);
        if (distance > 0 and distance < viewDistance){
            sum += prey->pos;
            count++;
        }
    }
    if (count == 0) return Vec2();
    sum /= (double)count;
    return sum;
}


void Prey::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators){
    acc = Vec2();
    acc += sepCoeff * Separation(preys);
    acc += Alignment(preys);
    acc += Cohesion(preys);
}
