#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>
#include "SFML/Graphics.hpp"

class Vec2{
public:
    Vec2(double x, double y) : x(x), y(y) {};
    Vec2() : Vec2(0.0, 0.0) {};

    Vec2 operator +(const Vec2& other) const {return Vec2(x + other.x, y + other.y);};
    Vec2& operator += (const Vec2& other){
        x += other.x;
        y += other.y;
        return *this;
    };

    Vec2 operator -(const Vec2& other) const {return Vec2(x - other.x, y - other.y);};
    Vec2& operator -=(const Vec2& other){
        x -= other.x;
        y -= other.y;
        return *this;
    };
    Vec2 operator*(const Vec2& other) const {return Vec2(x*other.x, y*other.y);};
    Vec2& operator*=(const Vec2& other){
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vec2 operator/(const Vec2& other) const {return Vec2(x/other.x, y/other.y);};
    Vec2& operator/=(const Vec2& other){
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vec2 operator*(double c) const {return Vec2(c*x, c*y);}
    Vec2& operator*=(double c){
        x *= c;
        y *= c;
        return *this;
    }

    Vec2 operator /(double c) const {return Vec2(x/c, y/c);};
    Vec2& operator /=(double c){
        x /= c;
        y /= c;
        return *this;
    }

    inline Vec2 T() const {return Vec2(y, x);}
    inline double dot(const Vec2& other) const {return (x*other.x + y*other.y);}

    inline double length() const {return sqrt(x*x + y*y);}
    inline double lengthSquared() const {return x*x + y*y;}

    double distance(const Vec2& other) const {return (other - *this).length();}
    double distanceSquared(const Vec2& other) const {return (other - *this).lengthSquared();}

    Vec2& normalize(){
        double len = length();
        if(len == 0.0){
            return *this;
        }
        *this *= 1.0/len;
        return *this;
    };

    void print(){
        std::cout << "[" << x << ", " << y << "]" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec){
        os << "[" << vec.x << ", " << vec.y << "]";
        return os;
    }

    inline sf::Vector2f toSf() const{
        return sf::Vector2f(x, y);
    }

    inline Vec2 rotate(double angle) const {
        // Angle in degrees -> radians
        angle *= M_PI/180.0;
        return Vec2(x*cos(angle) - y*sin(angle),
                    x*sin(angle) + y*cos(angle));
    }

    inline Vec2 rotateAround(double angle, const Vec2& center) const {
        return (*this - center).rotate(angle) + center;
    }

    void cap(double maxNorm){
        if(length() >= maxNorm){
            x = maxNorm*x/length();
            y = maxNorm*y/length();
        }
    }

    double x;
    double y;
};

inline Vec2 operator*(double f, const Vec2& vec){
    return Vec2(f*vec.x, f*vec.y);
}

#endif // VEC2_HPP
