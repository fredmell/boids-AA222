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

class Boid{
public:
  Boid(Vec2 x0, Vec2 v0) : _pos(x0), _vel(v0) {};
  Boid(Vec2 x0, Vec2 v0, bool isPred) : _pos(x0), _vel(v0), _isPred(isPred) {};

  void step();

  Vec2 pos(){return _pos;};
  Vec2 vel(){return _vel;};
  double directionAngle();
  void wrap(int, int);

  // Forces
  Vec2 Separation(std::vector<Boid> Boids);
  Vec2 Alignment(std::vector<Boid> Boids);
  Vec2 Cohesion(std::vector<Boid> Boids);

private:
  bool _isPred;
  Vec2 _pos;
  Vec2 _vel;
  Vec2 _acc;
  double _maxSpeed;
};

#endif // BOID_HPP
