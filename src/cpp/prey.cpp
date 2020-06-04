#include "prey.hpp"
#include "boid.hpp"
#include "predator.hpp"
#include "flock.hpp"

#include "SFML/Graphics.hpp"

Prey::Prey(Vec2 x0, Vec2 v0, double _separation_coeff, double _alignment_coeff, double _cohesion_coeff, double max_speed, double max_force)
: Boid(x0, v0, max_speed, max_force), separation_coeff(_separation_coeff), alignment_coeff(_alignment_coeff), cohesion_coeff(_cohesion_coeff){
    color = sf::Color::Green;
}

Vec2 Prey::separation(std::vector<Prey*>& preys){
    if(preys.size() == 0) return Vec2();
    Vec2 sum = Vec2();
    int count = 0;
    for(auto prey : preys){
        Vec2 diff = pos - prey->pos;
        double distance = diff.length();
        if(distance < 20){
            diff.normalize();
            diff /= distance;
            sum += diff;
            count++;
        }
    }
    if (count != 0) {
        sum /= (double)count;
        sum.setLen(max_speed);
        sum -= vel;
        sum.cap(max_force);
    }
    return sum;
}

Vec2 Prey::alignment(std::vector<Prey*>& preys){
    if(preys.size() == 0) return Vec2();
    Vec2 sum = Vec2();
    for (auto prey : preys){
        sum += prey->vel;
    }
    sum /= preys.size();
    sum.normalize();
    sum *= max_speed;
    sum -= vel;
    sum.cap(max_force);
    return sum;
}

Vec2 Prey::cohesion(std::vector<Prey*>& preys){
    if (preys.size() == 0) return Vec2();

    Vec2 center_of_mass = Vec2();
    for (auto prey : preys) {
        center_of_mass += prey->pos;
    }
    center_of_mass /= (double)preys.size();
    Vec2 sum = center_of_mass - pos;
    sum.setLen(max_speed);
    sum -= vel;
    sum.cap(max_force);
    return sum;
}

Vec2 Prey::centerPull(int width, int height){
    double dx, dy;
    if(pos.x > 0.9*width){
        dx = -1.0;
    }
    else if (pos.x < 0.1*width){
        dx = 1.0;
    }
    if(pos.y > 0.9*height){
        dy = -1.0;
    }
    if(pos.y < 0.1*height){
        dy = 1.0;
    }
    return Vec2(dx, dy);
}


void Prey::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators, int width, int height){
    neighbors = findNearestNeighbors(preys, view_distance);
    acc = 0;

    force_separation = separation(neighbors);
    force_alignment  = alignment(neighbors);
    force_cohesion   = cohesion(neighbors);
    force_center_pull = centerPull(width, height);
    acc += separation_coeff * force_separation;
    acc += alignment_coeff * force_alignment;
    acc += cohesion_coeff  * force_cohesion;
    acc.cap(max_force);
    acc += 3*force_center_pull;
}

void Prey::setFlock(Flock* _flock){
    flock = _flock;
    id_boid = flock->boids.size() - 1;
    id_prey = flock->preys.size() - 1;
}

std::vector<Prey*> Prey::findNearestNeighbors(const std::vector<Prey*>& preys, double max_distance){
    double distancesq;
    std::vector<Prey*> neighbors;
    for(auto prey: preys){
        distancesq = pos.distanceSquared(prey->pos);
        if(this != prey and distancesq < max_distance){
            neighbors.push_back(prey);
        }
    }
    return std::move(neighbors);
}

void drawForce(Prey *prey, sf::Vertex *line, sf::Color color, Vec2 &force) {
  auto center = prey->pos.toSf();
  line[0].position = center;
  line[1].position = center + force.toSf();
  line[0].color = color;
  line[1].color = color;
}

void Prey::drawForces(sf::Vertex* line){
    drawForce(this, line, sf::Color::Green, force_separation);
    drawForce(this, line + 2, sf::Color::Blue,  force_cohesion);
    drawForce(this, line + 4, sf::Color::Yellow, force_alignment);
    drawForce(this, line + 6, sf::Color::Magenta, force_center_pull);
}

void Prey::kill(){
    if(alive){
      alive = false;
      flock->addCausalty(this);
    }
}
