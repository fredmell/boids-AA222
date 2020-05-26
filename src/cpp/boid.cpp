#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "boid.hpp"
#include "vec2.hpp"
#include "flock.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Boid::Boid(Vec2 x0, Vec2 v0, double maxSpeed)
    : pos(x0), vel(v0), maxSpeed(maxSpeed){
        acc = Vec2();
  }

// Perform one time step. Return value is whether the boid is alive.
bool Boid::step(){

    // Update velocity using acceleration
    vel += acc;
    vel.cap(maxSpeed);

    // Update position using new velocity
    pos += vel;

    return alive;
}

void Boid::makeTriangle(sf::Vertex* triangle){
    auto angle = directionAngle() + 180;
    triangle[0].position = Vec2(pos.x-5, pos.y-5).rotateAround(angle, pos).toSf();
    triangle[1].position = Vec2(pos.x+5, pos.y-5).rotateAround(angle, pos).toSf();
    triangle[2].position = Vec2(pos.x, pos.y+10).rotateAround(angle, pos).toSf();
    triangle[0].color = color;
    triangle[1].color = color;
    triangle[2].color = color;
}

void Boid::drawVelocity(sf::Vertex* line){
    Vec2 direction = pos + 20 * vel;
    line[0].position = pos.toSf();
    line[1].position = direction.toSf();
}

void Boid::drawAcceleration(sf::Vertex *line) {
  auto direction = pos + 50 * acc;
  line[0].position = pos.toSf();
  line[1].position = direction.toSf();
  line[0].color = sf::Color::Red;
  line[1].color = sf::Color::Red;
}

void Boid::kill(){
    if(alive){
      alive = false;
      flock->addCausalty(this);
    }
}
