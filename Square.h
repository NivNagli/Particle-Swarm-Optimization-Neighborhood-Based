/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Square.h
 * Contact Information: itsniv@gmail.com
 */

#ifndef DRONE_RESCUE_SQUARE_H
#define DRONE_RESCUE_SQUARE_H

#include "Vec2D.h"

/*                                      Description:
 * The second class i chose to implement for the design of the program is "Square",
 * each type from this class will represent a square meter in our forest with two private fields.
 * ----------------------------------------------------------------------------------------
 * each type from this class will be a field in the advanced classes.
 * ----------------------------------------------------------------------------------------
 *                                     Convocation:
 * "Coordinates" : "Vec2D" variable that will contain the metric location of the "Square" in the forest.
 * "numOfAircrafts" (int): int variable that will count the number of aircraft's above the "Square" meter.
 * ----------------------------------------------------------------------------------------
 *                                    Additional functions:
 * Operators: prefix and postfix operators will help us update the number of aircraft above the square.
 * and the other functions are implementations for the basic operations.
 * ----------------------------------------------------------------------------------------
 * */

    /* Square fields: */
class Square {

private:
    Vec2D Coordinates;

    int numOfAircrafts;

public:
    /* Builders + The BiG 3 */

    Square();

    Square(const Square& s);

    Square(double xInit, double yInit, int new_Aircrafts);

    ~Square(){}

    Square& operator=(const Square& rhs);

    /* Setters and getters: */
    void setCoordinates(const Vec2D& new_Coordinates);

    void setnumOfAircraft(int new_num);

    Vec2D getCoordinates() const ;

    int getNumOfAircrafts() const;

    /* Useful operators: */
    Square& operator++();  //pre-fix: add 1 to each element

    const Square operator++(int);  //post-fix: add 1 to each element
    /* Notice, the int inside bracket. This int gives information to the compiler that it is the postfix version of operator.  TODO .. */

    Square& operator--();  //pre-fix: add 1 to each element

    const Square operator--(int);  //post-fix: add 1 to each element

    friend bool operator==(const Square& lhs, const Square& rhs); // i didnt use this operators in the end

    friend bool operator!=(const Square& lhs, const Square& rhs); // but i leave them because i want to remember how i create them.


};


#endif //DRONE_RESCUE_SQUARE_H
