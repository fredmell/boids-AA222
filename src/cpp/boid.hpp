#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "vec2.hpp"
#include "flock.hpp"

#include "SFML/Graphics.hpp"

class Boid{
public:
  Boid(Vec2 x0, Vec2 v0);

  double directionAngle();

  // Visualization methods
  void draw(sf::RenderWindow& window){window.draw(shape);};

  Vec2 pos;
  Vec2 vel;

  double maxSpeed;
  sf::CircleShape shape = sf::CircleShape(8,3);
  double markerSize = 3.0;
};

#endif // BOID_HPP
