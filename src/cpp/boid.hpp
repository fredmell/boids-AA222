#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Boid{
public:
    Boid(Vec2 x0, Vec2 v0, double maxSpeed = 1.0);

    bool step();

    inline double directionAngle() const {
            return static_cast<double>(std::atan2(vel.x, -vel.y) * 180.0 / M_PI);
    }

    double maxSpeed;
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;

    bool alive = true;

    // SFML visualization
    sf::Color color = sf::Color::Blue;

    //void draw(sf::RenderWindow& window){window.draw(shape);};
    void makeTriangle(sf::Vertex*);
};

#endif // BOID_HPP
