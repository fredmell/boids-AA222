#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

#include "flock.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Boid{
public:
  Boid(Vec2 x0, Vec2 v0);
  virtual ~Boid(){};

  void step();

  double directionAngle();
  Vec2 pos;
  Vec2 vel;
  Vec2 acc;

  // SFML visualization
  sf::CircleShape shape = sf::CircleShape(8,3);
  void draw(sf::RenderWindow& window){window.draw(shape);};
  double markerSize = 3.0;
};

#endif // BOID_HPP
