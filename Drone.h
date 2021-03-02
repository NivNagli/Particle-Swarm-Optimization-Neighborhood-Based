/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Drone.h
 * Contact Information: itsniv@gmail.com
 */

#ifndef DRONE_RESCUE_DRONE_H
#define DRONE_RESCUE_DRONE_H

#include "Square.h"
#include <iomanip>
using namespace std;

/*                                      Description:
 * The third class i chose to implement for the design of the program is "Drone", this is one of the advanced classes.
 * each type from this class will represent a Drone aircraft in the area of the program,
 * the class have 6 private fields which will be detailed below in the description of the "Convocation".
 * ----------------------------------------------------------------------------------------
 *                                     Convocation:
 *  Location: "Square" variable that will contain the current location (meter, meter) that the drone is above him.
 *
 *  Exact_Location:
 *  "Vec2D" variable that will contain the exact location of the drone in the surface,
 *  this field will make it easy for us to do the calculation for the program which require precise locations of the drones in the field.
 *
 *  Speed:
 *  "Vec2D" variable that will contain the exact speed of the drone,
 *  the "Vec2D" will make our calculations much easier because of the Vec2D class operators and methods.
 *
 *  personal_best:
 *  "Vec2D" variable that will contain the best personal position of the drone in relation to the target point.
 *
 *  serial_num (int) : int variable that will contain the drone location in the Drones array of our "Forest" class.
 *
 *  fly:
 *  boolean variable that will serve us with two edge cases, first is the case the drone took off from the target point.
 *  the second case is the update of the "personal_best" field in the first move because the drones "velocity_function"
 *  ["updateSpeed" method] can not work without an initialized vector.
 *  velocity = speed.
 * ----------------------------------------------------------------------------------------
 *                                    Additional functions:
 * OStream operator:
 * This is the only operator I have implemented for the class in addition to the operator=
 * i chose to implement the ostream operator to make the writing to the output file easier and readable.
 *
 * Vec2D nextExLocation():
 * This function will return the result of the calculation for the next location for the drone:
 * "Xi+1" =  next location, "Xi" = current location, "Vi" = current velocity:
 *                              Xi+1 = Xi + Vi
 *
 * updateSpeed(const Vec2D& global_best):
 * This function will return the result of the calculation from Particle Swarm Optimization (PSO) algorithm with
 * "neighbourhoods" standard:
 * " This topology allows all particles to communicate with all the other particles,
 * thus the whole swarm share the same best position "g" from a single particle. However,
 * this approach might lead the swarm to be trapped into a local minimum. "
 * Quoted: "https://en.wikipedia.org/wiki/Particle_swarm_optimization"
 *
 * ----------------------------------------------------------------------------------------
 *  #.Full description for the formula in the method.#
 */
class Drone {

private:
    Square Location;

    Vec2D Exact_Location;

    Vec2D Speed;

    Vec2D personal_best;

    int serial_num;

    bool fly;

public:
    /* Builders + The BiG 3 */

    Drone();

    Drone(const Drone& d);

    Drone(Square& new_Loc, Vec2D& new_Ex_Loc, Vec2D& new_speed, Vec2D& new_best, int new_s_num, bool flag);

    ~Drone(){}

    Drone& operator=(const Drone& rhs);

    // Setters and getters:

    void setLocation(const Square& new_location);

    void setExLocation(const Vec2D& new_Ex_location);

    void setSpeed(const Vec2D& new_speed);

    void setPbest(const Vec2D& new_P_best);

    void setSnum(int new_S_num);

    void setFly(bool flyy);

    Square getLocation() const;

    Vec2D getExLocation() const;

    Vec2D getSpeed() const;

    Vec2D getPbest() const;

    int getSnum() const;

    bool isFly() const;

    /* Useful operators:
     * i created one operator that is outside the Class scope because the first parameter is not of our class type.. */

    // Methods :

    Vec2D nextExLocation();

    void updateSpeed(const Vec2D& global_best);

    void personalBest(const Vec2D& target);


};
ostream& operator<<(ostream &out, const Drone &d);
// we need to announce the function outside the class scope because it activated by non class type.


#endif //DRONE_RESCUE_DRONE_H
