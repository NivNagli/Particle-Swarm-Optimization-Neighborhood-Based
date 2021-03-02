/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Drone.cpp.cc
 * Contact Information: itsniv@gmail.com
 */

#include "Drone.h"

Drone::Drone(): Location(0,0,0), Exact_Location(0,0), Speed(0,0), personal_best(0,0), serial_num(0), fly(false) {}

Drone::Drone(const Drone &d): Location(0,0,0), Exact_Location(0,0), Speed(0,0), personal_best(0,0), serial_num(0) {
    Location = d.Location;
    Exact_Location = d.Exact_Location;
    Speed = d.Speed;
    personal_best = d.personal_best;
    serial_num = d.serial_num;
    fly = d.fly;
}

Drone::Drone(Square &new_Loc, Vec2D& new_Ex_Loc, Vec2D &new_speed, Vec2D &new_best, int new_s_num,bool flag): Location(0,0,0), Exact_Location(0,0), Speed(0,0), personal_best(0,0), serial_num(0) {
    Location = new_Loc;
    Exact_Location = new_Ex_Loc;
    Speed = new_speed;
    personal_best = new_best;
    serial_num = new_s_num;
    fly = flag;
}

Drone &Drone::operator=(const Drone &rhs) {
    if(this != &rhs){
        this->Location = rhs.Location;
        this->Exact_Location = rhs.Exact_Location;
        this->Speed = rhs.Speed;
        this->personal_best = rhs.personal_best;
        this->serial_num = rhs.serial_num;
        this->fly = rhs.fly;
    }
    return *this;
}

void Drone::setLocation(const Square &new_location) {
    Location = new_location;
}

void Drone::setExLocation(const Vec2D& new_Ex_location) {
    Exact_Location = new_Ex_location;
}

void Drone::setSpeed(const Vec2D &new_speed) {
    Speed = new_speed;
}

void Drone::setPbest(const Vec2D &new_P_best) {
    personal_best = new_P_best;
}

void Drone::setSnum(int new_S_num) {
    serial_num = new_S_num;
}

Square Drone::getLocation() const {
    return Location;
}

Vec2D Drone::getExLocation() const {
    return Exact_Location;
}

Vec2D Drone::getSpeed() const {
    return Speed;
}

Vec2D Drone::getPbest() const {
    return personal_best;
}

int Drone::getSnum() const {
    return serial_num;
}

bool Drone::isFly() const {
    return fly;
}

void Drone::setFly(bool flyy) {
    this->fly = flyy;
}

Vec2D Drone::nextExLocation() {
    Vec2D Coordinates = Exact_Location + Speed;
    return Coordinates;
}

void Drone::updateSpeed(const Vec2D &global_best) {
    /*                                          Algorithm:
     * vi(t+1) = ( w * v(t) ) + r1i * c1 * ( y(t) - li(t+1) ) + r2i * c2 * ( yi(t) - li(t+1) )
     * i created the operators of the "Vec2D" objects to make the calculate look readable.
     * -----------------------------------------------------------------------------------------------------------------
     *                                          Legend:
     *
     * vi = velocity => in our program known as Speed.
     *
     * t = the latest time point => in our program because we iterate each drone we can control the time point.
     *
     * y(t) = the location of the personal_best in the same time point.
     *
     * yi(t) = the location of the global_best in the same time point.
     *
     * r1i & r2i = random numbers we creating "randomly" in each time point for the calculate of the algorithm.
     *
     * c1, c2 = constants that produce acceleration to the next direction.
     *
     * w = "Inertia Weight": " The role of the inertia weight  is considered very important in PSO convergence behavior.
     * the inertia weight is applied to control the impact of the previous history of velocities on the current velocity. "
     * Quoted: "https://www.researchgate.net/publication/275066387_Novel_Particle_Swarm_Optimization_and_Its_Application_in_Calibrating_the_Underwater_Transponder_Coordinates"
     *
     */

    double c1=1 , c2=2, w=0.5;
    double r1 = ((double) (rand()) / RAND_MAX);
    double r2 = ((double) (rand()) / RAND_MAX);

    Speed = (Speed * w) + ( (personal_best - Exact_Location) * r1 * c1 ) + ( (global_best - Exact_Location) * r2 * c2 );
}

void Drone::personalBest(const Vec2D &target) {
    if(!fly) {  // first we check if the drone just took off, in case he took off the place he lunch from will be his p_best.
        personal_best = Exact_Location;
        fly = true;
        return;
    }
    double new_dis = Exact_Location.distance(target);
    if(new_dis < personal_best.distance(target)){
        personal_best = Exact_Location;
    }
}


ostream &operator<<(ostream &out, const Drone &d) {
    /* we use "fixed" and "setprecision()" to print the number with two digits after the dot. */
    return (out <<  fixed << showpoint << setprecision(2) << d.getExLocation().getX() << " " << setprecision(2) << d.getExLocation().getY());
}
