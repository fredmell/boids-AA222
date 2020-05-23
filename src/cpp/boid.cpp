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
        //shape = sf::CircleShape(8,3);
        //shape.setPosition(pos.x, pos.y);
        //shape.setOutlineColor(sf::Color(255,255,255));
        //shape.setFillColor(sf::Color::Blue);
        //shape.setOutlineThickness(0.5);
        //shape.setRadius(3.0);
  }

// Perform one time step. Return value is whether the boid is alive.
void Boid::step(){

    // Update velocity using acceleration
    vel += acc;

    // Update position using new velocity
    pos += vel;
}

void Boid::makeTriangle(sf::Vertex* triangle){
    triangle[0].position = sf::Vector2f(pos.x-1, pos.y-1);
    triangle[1].position = sf::Vector2f(pos.x+1, pos.y-1);
    triangle[2].position = sf::Vector2f(pos.x, pos.y+1);
    triangle[0].color = color;
    triangle[1].color = color;
    triangle[2].color = color;
}
