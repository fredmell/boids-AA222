/*
TODO:
- Add the angle reduced view range, i.e. make it depend also on angle and not only distance.
- Implement the three first forces to use
- Calibrate the coefficients
*/

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
  void draw(sf::RenderWindow& window){window.draw(_shape);};

  Vec2 pos;
  Vec2 vel;

private:
  double _maxSpeed;
  sf::CircleShape _shape = sf::CircleShape(8,3);
  double _size = 3.0;
};

#endif // BOID_HPP
