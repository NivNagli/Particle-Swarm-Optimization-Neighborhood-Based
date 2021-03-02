/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Vec2D.h
 * Contact Information: itsniv@gmail.com
 */
#ifndef DRONE_RESCUE_VEC2D_H
#define DRONE_RESCUE_VEC2D_H

#include <iostream>
#include <cstdlib>
#include <cmath>

/*                                      Description:
 * The first class i choose to implement is "Vec2D", each type in this class will be a field in the advanced classes,
 * this class is a part represent of a two-dimensional vector with the fields of (x,y) coordinates.
 * ----------------------------------------------------------------------------------------
 *                                     Convocation:
 * x (int): a field that will contain the value of x in the euclidean axis.
 * y (int): a field that will contain the value of y in the euclidean axis.
 * ----------------------------------------------------------------------------------------
 *                                    Additional functions:
 * Operators that will help us calculate easily, the operators will help the code look more readable and usable.
 * methode : distance(const Vec2D& v): this function will get a Vec2D variable as argument and will return us the result
 * of the euclidean distance between the two points.
 * ----------------------------------------------------------------------------------------
 * */

            /* Vec2D fields: */
class Vec2D {

private:
    double x,y;


public:
    /* Builders + The BiG 3 */

    Vec2D();

    Vec2D(double x_val ,double y_val);

    ~Vec2D(){}

    Vec2D(const Vec2D& v);

    Vec2D& operator=(const Vec2D &rhs);


    /* Setters and getters: */

    void setX(double new_x) {x = new_x ;}

    void setY(double new_y) {y = new_y;}

    void setXY(double new_x, double new_y) {x = new_x ; y = new_y;}

    double getX() const {return this->x;}

    double getY() const {return this->y; }



    /* Useful operators: */

    Vec2D operator+(const Vec2D& v) const;

    Vec2D operator-(const Vec2D& v) const;

    Vec2D operator*(const double scalar) const;

    void operator+=(const Vec2D& v);

    void operator-=(const Vec2D& v);

    void operator*=(const Vec2D& v);

    void operator*=(const double scalar);

    friend bool operator==(const Vec2D& lhs, const Vec2D& rhs);

    friend bool operator!=(const Vec2D& lhs, const Vec2D& rhs);

    // Methods :

    double distance(const Vec2D& v) const;

};


#endif //DRONE_RESCUE_VEC2D_H
