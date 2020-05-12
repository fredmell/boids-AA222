#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "flock.hpp"
#include "boid.hpp"
#include "vec2.hpp"

#include "SFML/Graphics.hpp"

Boid::Boid(Vec2 x0, Vec2 v0)
  : _pos(x0), _vel(v0) {
    _shape.setPosition(_pos.x, _pos.y);
    _shape.setOutlineColor(sf::Color(255,255,255));
    _shape.setFillColor(sf::Color::Blue);
    _shape.setOutlineThickness(0.5);
    _shape.setRadius(_size);
  }

Boid::Boid(Vec2 x0, Vec2 v0, bool isPred)
  : Boid(x0, v0) {
    if(isPred){
      _shape.setFillColor(sf::Color::Red);
    }
    _isPred = isPred;
  }

// Perform one time step. Return value is whether the boid is alive.
void Boid::step(std::vector<Boid>& boids, bool& alive){
  // Apply forces
  Vec2 dv;
  if( this->isPredator() ){
    double factor = 1.2;
    dv = this->hunt(boids).normalize();
    _vel = dv;
    _vel *= factor;
  }

  if (this->isPrey() ){
    alive = not this->predClose(boids);
  }

  // Update position using new velocity
  _pos += _vel;

  // Update position and rotation of SFML shape
  _shape.setPosition(_pos.x, _pos.y);
  _shape.setRotation(this->directionAngle());
}

Vec2 Boid::hunt(const std::vector<Boid>& boids){
  // Simply follow the nearest prey
  Vec2 force;
  unsigned idx = 0;
  double dist = 1000.0;
  double newDist;
  for(unsigned i=0; i<boids.size(); i++){
    Boid otherBoid = boids.at(i);
    if( otherBoid.isPrey() ){
      newDist = this->pos().distance(otherBoid.pos());
      if( newDist < dist ){
        force = (otherBoid.pos() - this->pos());
      }
    }
  }
  return force;
}

bool Boid::predClose(std::vector<Boid>& boids){
  double closeDist = 5;
  double dist;
  for(unsigned i=0; i<boids.size(); i++){
    Boid otherBoid = boids.at(i);
    if( otherBoid.isPredator() ){
      dist = this->pos().distance(otherBoid.pos());
      if(dist < closeDist){
        return true;
      }
    }
  }
  return false;
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
