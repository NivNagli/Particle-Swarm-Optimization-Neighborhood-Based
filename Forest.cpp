/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Forest.cpp.cc
 * Contact Information: itsniv@gmail.com
 */
#include <fstream>
#include "Forest.h"


Forest::Forest(int x, int y, string *locations): Area(NULL), Drones(NULL), Target(0,0), global_best(0,0), min_border(x), max_border(y), drones_counter(0) {
    // Initialization and testing procedures
    ifstream f4("target.csv");  // we are getting the target from a file.
    string target_str;
    getline(f4, target_str);
    f4.close();
    stringstream stream(target_str);

    int surface = max_border - min_border;  // surface represent the length of a line in our surface for example:
    // [-500, 500] are the borders so the matrix surface is: 1000x1000.
    // to really understand why i did that read the documentation that appear in the .h file, ["Convocation"].

    double xc = 0 , yc = 0 ;  // double x and y to save the x&y coordinates x_c = x coordinates.
    char comma;  // Because we are working with csv file his coordinates are separate by comma...
    stream >> xc;
    stream >> comma;

    if(!(stream >> yc)){
        throw invalid_argument("invalid input");  // that mean the line with the target coordinates didnt contain 2 numbers.
    }

    if(!( stream.eof()) ) {
        throw invalid_argument("invalid input");  // invalid input because need to contain exactly 2 numbers.
    }

    if(xc < min_border || yc < min_border || xc > max_border || yc > max_border){
        throw invalid_argument("invalid input");  // we need to stop the program in case we get invalid coordinates.
    }

    Target = Vec2D(xc,yc);  // the case the Target coordinates are valid.
    /* until this point we just receive the coordinates for the "Target" point and we make sure they are valid coordinates */

    stream.clear();  // now we read the number of drones
    stream.str(locations[0]);  // the number of the drones should be in the first line of the text file.

    int drones = 0;
    stream >> drones;
    if(!( stream.eof()) || drones < 2 ){
        throw invalid_argument("invalid input");
    }
    this->drones_counter = drones;


    /* im adding 1 to the min_border and max_border because the allocation start from 0 */
    Area = new Square*[surface*surface];  // allocate the dynamic objects arrays on the heap.
    Drones = new Drone[drones];  // ^^

    for(int i = 0 ; i < surface+1 ; i++) {  // initialize every space cell in our forest
        Area[i] = new Square[surface + 1];
        for(int j = 0 ; j < surface + 1 ; j++){
            Area[i][j] = Square(i,j,0);
        }
    }


    for(int i = 0 ; i < drones ; i++) {  // Time to create the drones array.
        stream.clear();
        stream.str(locations[i+1]);  // because our drone coordinates is in the second line we start from i + 1
        stream >> xc >> yc;

        if( stream.eof() ){
            cleanObj();
            throw invalid_argument("invalid input");  // that mean the line didnt contain at least 4 coordinates
        }

        if(xc < min_border || yc < min_border || xc > max_border || yc > max_border){
            cleanObj();
            throw invalid_argument("invalid input");  // we need to stop the program in case we get invalid coordinates.
        }

        Vec2D ex_location = Vec2D(xc,yc);  // create the Vec2D "exact_location" for our drone.
        Area[(int) xc + max_border][(int) yc + max_border]++;  // update the number of drones above the square the drone take off.
        Drones[i].setLocation(Area[(int) xc + max_border][(int) yc + max_border]);  // update the "Location" field in our drone.
        Drones[i].setExLocation(ex_location);  // update the Vec2D field in our drone to his exact_location

        // now we will try to update the drone first velocity if we fail to do so we will throw exception
        stream >> xc;

        if(!(stream >> yc)){
            cleanObj();
            throw invalid_argument("invalid input");  // that mean the line didnt contain at least 4 coordinates
        }

        if(!( stream.eof()) ) {  // that mean the line contain more then 4 coordinates..
            cleanObj();
            throw invalid_argument("invalid input");
        }

        if(xc < min_border || yc < min_border || xc > max_border || yc > max_border){
            cleanObj();
            throw invalid_argument("invalid input");  // we need to stop the program in case we get invalid coordinates.
        }

        Vec2D speed = Vec2D(xc,yc);  // create the vector exact_location for our drone.
        Drones[i].setSpeed(speed);
        Drones[i].setSnum(i); // update the serial number of the drone to his index in the Drones array.
        Drones[i].personalBest(Target);  // update the drone personal best full doc in "personalBest" methode in Drone class.
    }
    findGbest1();

}

Forest::Forest(const Forest &f): Area(NULL), Drones(NULL), Target(0,0), global_best(0,0), min_border(0), max_border(0), drones_counter(0) {
    Area = f.Area;
    Drones = f.Drones;
    Target = f.Target;
    global_best = f.global_best;
    min_border = f.min_border;
    max_border = f.max_border;
    drones_counter = f.drones_counter;
}

Forest::~Forest() {
    for(int i = 0 ; i < min_border + 1 ; i++){
        delete [] Area[i];
    }
    delete Area;

    delete [] Drones;
}

Forest &Forest::operator=(const Forest &rhs) {
    if(this != &rhs){
        this->Area = rhs.Area;
        this->Drones = rhs.Drones;
        this->Target = rhs.Target;
        this->global_best = rhs.global_best;
        this->min_border = rhs.min_border;
        this->max_border = rhs.max_border;
    }
    return *this;
}

Square **Forest::getArea() const {
    return Area;
}

void Forest::setArea(Square **area) {
    Area = area;
}

Drone *Forest::getDrones() const {
    return Drones;
}

void Forest::setDrones(Drone *drones) {
    Drones = drones;
}

const Vec2D &Forest::getTarget() const {
    return Target;
}

void Forest::setTarget(const Vec2D &target) {
    Target = target;
}

const Vec2D &Forest::getGlobalBest() const {
    return global_best;
}

void Forest::setGlobalBest(const Vec2D &globalBest) {
    global_best = globalBest;
}

int Forest::getWidth() const {
    return min_border;
}

void Forest::setWidth(int new_width) {
    Forest::min_border = new_width;
}

int Forest::getLength() const {
    return max_border;
}

void Forest::setLength(int new_length) {
    Forest::max_border = new_length;
}

int Forest::getDronesCounter() const {
    return drones_counter;
}

void Forest::setDronesCounter(int dronesCounter) {
    drones_counter = dronesCounter;
}



void Forest::findGbest1() {
    /* imitation of a simple algorithm for finding an extreme point in array but in this case we look for the
     * lowest distance in the two-dimensional space between the target and the locations of the drones for the first iteration.
     * */

    Vec2D best_result = Drones[0].getExLocation();
    double closest = best_result.distance(Target);

    for(int i = 1 ; i < drones_counter ; i++){
        Vec2D temp_result = Drones[i].getExLocation();
        double temp = temp_result.distance(Target);
        if(closest > temp){
            best_result = Drones[i].getExLocation();
            closest = temp;
        }
    }
    global_best = best_result;
}

void Forest::moveDrones() {
    /* This function will work according to some main rules:
     * 1) update your next speed and then your next location.
     * 2) update the personal best if necessary.
     * 3) after all the drones made the first 2 rules check if one of the drones is in new global_best.
     *
     * # Note: when i access to the "Area" array i'm adding max_border value to the variable i noted why i'm doing this
     * in the .h file.
     */
    for(int i = 0 ; i < drones_counter ; i ++){
        Drones[i].updateSpeed(global_best);  // here we update the new speed of the drone.
        Vec2D new_location = Drones[i].nextExLocation();
        if( (new_location.getX() < min_border) || (new_location.getX() > max_border))  {
            if (new_location.getX() < min_border ) new_location.setX(min_border);
            else new_location.setX(max_border);
        }

        if( (new_location.getY() < min_border) || (new_location.getY() > max_border))  {
            if (new_location.getY() < min_border ) new_location.setY(min_border);
            else new_location.setY(max_border);
        }

        // because the squares are in a full metric precision we need to round down the exact location.
        Area[(int) Drones[i].getExLocation().getX() + max_border][(int) Drones[i].getExLocation().getY() + max_border] --; // updates the surface cell in the area where the drone left it
        Area[(int) new_location.getX() + max_border][(int) new_location.getY() + max_border] ++; // updates the surface cell in the area where the drone reached

        Drones[i].setExLocation(new_location);  // now after we calculate the new speed with the "old" location we can set the new location.
        Drones[i].setLocation( (Area[(int) new_location.getX() + max_border][(int) new_location.getY() + max_border]) ); // update to the new location square
        // we use the cast for (int) to take only the integer part of the number because the squares are assigned by the metric method.

        Drones[i].personalBest(Target);  // here we check if the drone is in new personal best
    }
    findGbest2();  // after we move all the drones we need to update the new global best coordinates

}

bool Forest::TargetFound() {
    /* We approach the square in the location of the target coordinates rounder down because our square indexing is in
     * the full meter size and the target coordinates are more accurate. */

    if(Area[(int) Target.getX() + max_border][(int) Target.getY() + max_border].getNumOfAircrafts() > 0) return true;
    /* if number of drones in area[(int) x_target][(int) y_target] > 0 return true. */

    return false;
}

ostream &Forest::printLocations(ostream &to) {
    for(int i = 0 ; i < drones_counter ; i++ ) {
        to << Drones[i] << endl;
    }
    return to;
}

void Forest::cleanObj() {
    // method that mimic the dtor, we need her for the builder exceptions handle...
    // because if we throw a exception from the builder we need to clean the heap manually because the dtor will not be activate.
    for(int k = 0 ; k < (1 + max_border - min_border) ; k++){
        delete [] Area[k];
    }
    delete Area;

    delete [] Drones;
}

void Forest::findGbest2() {
    // Second version for the rest of the iterations
    double closest = global_best.distance(Target);
    for(int i = 1 ; i < drones_counter ; i++){
        Vec2D temp_result = Drones[i].getExLocation();
        double temp = temp_result.distance(Target);
        if(closest > temp){
            global_best = Drones[i].getExLocation();
            closest = temp;
        }
    }
}












