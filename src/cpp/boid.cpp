#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "boid.hpp"
#include "vec2.hpp"

void Boid::step(){
  _pos += _vel;
}

void Boid::wrap(int width, int height){
  double dx = 0.0;
  double dy = 0.0;

  if(_pos.x < 0.0){
    dx = static_cast<double>(width);
  }
  else if(_pos.x > width){
    dx = - static_cast<double>(width);
  }
  if(_pos.y < 0.0){
    dy = static_cast<double>(height);
  }
  else if(_pos.y > height){
    dy = - static_cast<double>(height);
  }

  _pos += Vec2(dx, dy);
}

double Boid::directionAngle(){
  return static_cast<double>(std::atan2(_vel.x, -_vel.y) * 180 / M_PI);
}
