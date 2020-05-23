#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Boid{
public:
    Boid(Vec2 x0, Vec2 v0);

    void step();

    inline double directionAngle() const {
            return static_cast<double>(std::atan2(vel.x, -vel.y) * 180.0 / M_PI);
    }

    Vec2 pos;
    Vec2 vel;
    Vec2 acc;

    // SFML visualization
    //sf::CircleShape shape;
    sf::Color color = sf::Color::Blue;

    //void draw(sf::RenderWindow& window){window.draw(shape);};
    void makeTriangle(sf::Vertex*);
};

#endif // BOID_HPP
