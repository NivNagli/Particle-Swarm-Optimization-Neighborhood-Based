/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Vec2D.cpp.cc
 * Contact Information: itsniv@gmail.com
 */


#include "Vec2D.h"
using namespace std;



Vec2D::Vec2D() : x(0), y(0)  {}
Vec2D::Vec2D(double x_val, double y_val) : x(x_val), y(y_val) {}

Vec2D::Vec2D(const Vec2D &v) {
    x = v.x;
    y = v.y;
}

Vec2D &Vec2D::operator=(const Vec2D &rhs) {
    if(this != &rhs){
        this->x = rhs.getX();
        this->y = rhs.getY();
    }
    return *this;
}

Vec2D Vec2D::operator+(const Vec2D &v) const {
    return Vec2D( (x + v.x), (y + v.y) );
}

Vec2D Vec2D::operator-(const Vec2D &v) const {
    return Vec2D( (x - v.x), (y - v.y) );
}

Vec2D Vec2D::operator*(const double scalar) const {
    return Vec2D((x * scalar), (y * scalar));
}

void Vec2D::operator+=(const Vec2D &v)  {
    x += v.x;
    y += v.y;
}

void Vec2D::operator-=(const Vec2D &v) {
    x -= v.x;
    y -= v.y;
}

void Vec2D::operator*=(const Vec2D &v) {
    x *= v.x;
    y *= v.y;
}



void Vec2D::operator*=(const double scalar) {
    x*=scalar;
    y*=scalar;
}

bool operator==(const Vec2D &lhs, const Vec2D &rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) ;
}

bool operator!=(const Vec2D &lhs, const Vec2D &rhs) {
    return !( (lhs.x == rhs.x) && (lhs.y == rhs.y) ) ;
}

double Vec2D::distance(const Vec2D &v) const {
    /* A method that calculates the distance between two vectors using the fitness formula:
     *  (X - X_target)^2 + (Y - Y_target)^2
     */

    double xs = pow((this->x - v.x),2);  // (x - xt) ^ 2
    double ys = pow((this->y - v.y),2);  // (y - yt) ^ 2
    return xs + ys;
}



















