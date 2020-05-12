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
  Boid(Vec2 x0, Vec2 v0, bool isPred);

  Vec2 pos(){return _pos;};
  Vec2 vel(){return _vel;};
  bool isPredator(){return _isPred;};
  bool isPrey(){return not _isPred;}
  double directionAngle();
  void wrap(int, int);
  void draw(sf::RenderWindow& window){window.draw(_shape);};

  void step(std::vector<Boid>& boids, bool& alive);
  bool predClose(std::vector<Boid>& boids);

  // Forces
  Vec2 separation(const std::vector<Boid>& boids);
  Vec2 alignment(const std::vector<Boid>& boids);
  Vec2 cohesion(const std::vector<Boid>& boids);
  Vec2 flee(const std::vector<Boid>& boids);
  Vec2 hunt(const std::vector<Boid>& boids);

private:
  bool _isPred;
  Vec2 _pos;
  Vec2 _vel;
  double _maxSpeed;
  sf::CircleShape _shape = sf::CircleShape(8,3);
  double _size = 3.0;
};

#endif // BOID_HPP
