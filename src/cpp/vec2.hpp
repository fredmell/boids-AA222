#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>

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

    double x;
    double y;
};

#endif // VEC2_HPP
