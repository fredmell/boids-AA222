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

  double directionAngle();
  Vec2 pos;
  Vec2 vel;
  Vec2 acc;

  // SFML visualization
  sf::CircleShape shape;
  void draw(sf::RenderWindow& window){window.draw(shape);};
};

#endif // BOID_HPP
