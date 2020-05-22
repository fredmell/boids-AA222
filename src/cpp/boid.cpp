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
        shape.setPosition(pos.x, pos.y);
        shape.setOutlineColor(sf::Color(255,255,255));
        shape.setFillColor(sf::Color::Blue);
        shape.setOutlineThickness(0.5);
        shape.setRadius(markerSize);
  }

double Boid::directionAngle(){
    return static_cast<double>(std::atan2(vel.x, -vel.y) * 180.0 / M_PI);
}

// Perform one time step. Return value is whether the boid is alive.
void Boid::step(){

    // Update velocity using acceleration
    vel += acc;

    // Update position using new velocity
    pos += vel;

    // Update position and rotation of SFML shape
    shape.setPosition(pos.x, pos.y);
    shape.setRotation(directionAngle());
}
