#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "boid.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Boid::Boid(Vec2 x0, Vec2 v0)
    : pos(x0), vel(v0) {
        acc = Vec2();
  }

// Perform one time step. Return value is whether the boid is alive.
bool Boid::step(){

    // Update velocity using acceleration
    vel += acc;
    vel.normalize();

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
