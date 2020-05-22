#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "flock.hpp"
#include "boid.hpp"
#include "vec2.hpp"

#include "SFML/Graphics.hpp"

Boid::Boid(Vec2 x0, Vec2 v0)
  : pos(x0), vel(v0) {
    shape.setPosition(_pos.x, _pos.y);
    shape.setOutlineColor(sf::Color(255,255,255));
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.5);
    shape.setRadius(_size);
  }

double Boid::directionAngle(){
return static_cast<double>(std::atan2(vel.x, -vel.y) * 180 / M_PI);
}

// Perform one time step. Return value is whether the boid is alive.
void Boid::step(std::vector<Boid>& boids, bool& alive){

  // Update position using new velocity
  pos += vel;

  // Update position and rotation of SFML shape
  shape.setPosition(pos.x, pos.y);
  shape.setRotation(directionAngle());
}

// Vec2 Boid::hunt(const std::vector<Prey>& preyBoids){
//   // Simply follow the nearest prey
//   Vec2 force;
//   unsigned idx = 0;
//   double dist = 1000.0;
//   double newDist;
//   for(unsigned i=0; i<boids.size(); i++){
//     Boid otherBoid = boids.at(i);
//     if( otherBoid.isPrey() ){
//       newDist = this->pos().distance(otherBoid.pos());
//       if( newDist < dist ){
//         force = (otherBoid.pos() - this->pos());
//       }
//     }
//   }
//   return force;
// }

// bool Prey::predClose(const std::vector<Predator>& predators){
//   double closeDist = 5;
//   double dist;
//   for(unsigned i=0; i<boids.size(); i++){
//     Boid otherBoid = boids.at(i);
//     if( otherBoid.isPredator() ){
//       dist = this->pos().distance(otherBoid.pos());
//       if(dist < closeDist){
//         return true;
//       }
//     }
//   }
//   return false;
// }
