#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Flock;

class Boid{
public:
    Boid(Vec2 x0, Vec2 v0, double maxSpeed = 1.0, double _max_force = 0.1);

    void step();

    inline double directionAngle() const {
            return static_cast<double>(std::atan2(vel.x, -vel.y) * 180.0 / M_PI);
    }

    //void draw(sf::RenderWindow& window){window.draw(shape);};
    void makeTriangle(sf::Vertex*);
    void drawVelocity(sf::Vertex *line);
    void drawAcceleration(sf::Vertex *line);

    inline bool isAlive() const {return alive;};
    virtual void setFlock(Flock*) = 0;

    Flock* flock;
    int id_boid = -1;

    const double max_speed;
    const double max_force;
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;

    std::vector<Boid*> neighbors;

    // SFML visualization
    sf::Color color = sf::Color::Blue;

  protected:
    bool alive = true;
};

#endif // BOID_HPP
