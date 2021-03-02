/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Forest.h
 * Contact Information: itsniv@gmail.com
 */

#ifndef DRONE_RESCUE_FOREST_H
#define DRONE_RESCUE_FOREST_H

#include "Drone.h"
#include <string>
#include <sstream>
#include <stdexcept>

/*                                      Description:
 *
 * the fourth class i chose to implement for the design of the program is "Forest", this is our second advanced class.
 * each type from this class will represent area of a forest that contain a swarm of drones with at least 2 objects,
 * this object will be our main tool in the main code file.
 * ----------------------------------------------------------------------------------------
 *                                      Side note:
 *
 * we have here a use of a nice feature of the language
 * and that is the case of trowing exception from the constructor:
 * because the program works with inputs that are not created by her we need to make sure they are written properly,
 * in order not to run along the inputs twice we will perform the tests on the inputs in the custom builder and if
 * we detect an error in the inputs we will throw "invalid_argument" exception, then the builder will stop his actions
 * and we will make sure to release all the memory that the object has used from the heap until the error appears,
 * we will catch the exception in the "main" file and we will stop the program there and notify the user about the error.
 * ----------------------------------------------------------------------------------------
 *                                     Convocation:
 * ## Note: because the drones surface can explore negative coordinates in the surface and our surface is represented ##
 *  by "Square" array we are working according this rules:
 *  any time we want to update / access square in the surface we taking the drone location + max_border for example:
 *  drone location = (-499.8, -500), min border = -500, max border = 500
 *  so the drone will locate in the surface array in index (1, 0) => ( (int) x + max border, (int) y + max_border)
 *  so in the example the surface will be a matrix 1000x1000 so the array will contain 1000*1000 cells.
 *
 * in order to make for us easy life i create variable "surface" that will be max_border - min border.   read note^^
 * "Area": Square** [surface*surface] # surface description ^^^ #
 * i chose the object to be dynamic allocated object in order for the object to be able to represent
 * different sizes of "Forest" spaces, each variable in the matrix will represent a square meter in the forest.
 *
 * Drones: Drone* [Drone array aka "Swarm"]:
 * a dynamic allocated object from the same reasons as the "Area" field each variable in the object will represent
 * drone from our swarm.
 *
 * Target: "Vec2D" object that will contain the exact location of our swarm target.
 *
 * global_best: "Vec2D" object that will contain the global_best location our swarm reached until that point.
 *
 * min_border, max_border, drones_counter (int): min_border and max_border will contain the surface borders
 * and the drones_counter will contain the number of objects in our swarm.
 * ----------------------------------------------------------------------------------------
 *                                    Additional functions:
 * findGbest():
 * This function will be activated each time after all the objects in our swarm made their move
 * and after they updated their best personal locations until that time point,
 * the function will check if one of the swarm objects has arrived to a new global best location of the entire swarm
 * and that happens we will update the new "global_best".
 * I made two versions of "findGbest" on for the first time iteration and the second one for the rest of the iterations.
 *
 * void moveDrones():
 * this function will perform one movement of the swarm in the forest area
 * and will take care of updating all the data in the objects after the move.
 * # Full documentation in the function implementation. #
 *
 * bool TargetFound():
 * this is a method from my original implementation that can help for other versions of the PSO algorithm,
 * this method checks if one of the drones from the swarm is above the target.
 * ----------------------------------------------------------------------------------------
 *
 */

/* Square fields: */
class Forest {

private:
    Square** Area;

    Drone* Drones;

    Vec2D Target;

    Vec2D global_best;

    int min_border, max_border, drones_counter;


public:
    /* Builders + The BiG 3 */
    Forest(): Area(NULL), Drones(NULL), Target(0,0), global_best(0,0), min_border(0), max_border(0), drones_counter(0) {}

    Forest(int x, int y, string locations[]);  // The main constructor of our program because we cant use the basic one.

    Forest(const Forest& f);

    ~Forest();

    Forest& operator=(const Forest& rhs);


    // Setters and getters:
    Square **getArea() const;

    void setArea(Square **area);

    Drone *getDrones() const;

    void setDrones(Drone *drones);

    const Vec2D &getTarget() const;

    void setTarget(const Vec2D &target);

    const Vec2D &getGlobalBest() const;

    void setGlobalBest(const Vec2D &globalBest);

    int getWidth() const;

    void setWidth(int width);

    int getLength() const;

    void setLength(int length);

    int getDronesCounter() const;

    void setDronesCounter(int dronesCounter);

    // Methods :
    void findGbest1();
    void findGbest2();

    void moveDrones();

    bool TargetFound();

    void cleanObj();

    ostream& printLocations(ostream &to);
};


#endif //DRONE_RESCUE_FOREST_H
