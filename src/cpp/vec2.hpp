#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>

class Vec2{
public:
  Vec2(double x, double y) : x(x), y(y) {};
  Vec2() : Vec2(0.0, 0.0) {};

  Vec2 operator +  (Vec2 other){return Vec2(x + other.x, y + other.y);};
  Vec2& operator += (Vec2 other){
    x += other.x;
    y += other.y;
    return *this;
  };

  Vec2 operator -  (Vec2 other){return Vec2(x - other.x, y - other.y);};
  Vec2& operator -= (Vec2 other){
    x -= other.x;
    y -= other.y;
    return *this;
  };

  Vec2 operator *  (double c){return Vec2(c*x, c*y);};
  Vec2& operator *= (double c){
    x *= c;
    y *= c;
    return *this;
  };

  Vec2 operator /  (double c){return Vec2(x/c, y/c);};
  Vec2& operator /= (double c){
    x /= c;
    y /= c;
    return *this;
  };

  double dot(Vec2 other){return (x*other.x + y*other.y);};

  double length(){return sqrt(x*x + y*y);};

  double distance(Vec2 other){return (other - *this).length();};

  Vec2 normalized(){
    double len = length();
    if(len == 0.0){
      len = 1.0;
    }
    return Vec2(x/len, y/len);
  };

  void print(){
    std::cout << "[" << x << ", " << y << "]" << std::endl;
  }

  double x;
  double y;
};

#endif // VEC2_HPP
