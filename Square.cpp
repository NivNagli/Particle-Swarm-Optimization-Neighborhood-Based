/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: Square.cpp.cc
 * Contact Information: itsniv@gmail.com
 */

#include "Square.h"

Square::Square(): Coordinates(0,0), numOfAircrafts(0) {}

Square::Square(const Square &s): Coordinates(0,0), numOfAircrafts(0) {
    Coordinates = s.Coordinates;
    numOfAircrafts = s.numOfAircrafts;
}

Square::Square(double xInit, double yInit, int new_Aircrafts):Coordinates(0,0),numOfAircrafts(0) {
    Coordinates = Vec2D(xInit, yInit);
    numOfAircrafts = new_Aircrafts;
}

Square &Square::operator=(const Square &rhs) {
    if(this != &rhs){
        this->Coordinates = rhs.getCoordinates();
        this->numOfAircrafts = rhs.getNumOfAircrafts();
    }
    return *this;
}

void Square::setCoordinates(const Vec2D &new_Coordinates) {
    Coordinates = new_Coordinates;
}

void Square::setnumOfAircraft(int new_num) {
    this->numOfAircrafts = new_num;
}

Vec2D Square::getCoordinates() const {
    return Coordinates;
}

int Square::getNumOfAircrafts() const {
    return numOfAircrafts;
}

Square &Square::operator++() {
    numOfAircrafts = numOfAircrafts + 1;
    return *this;
}

const Square Square::operator++(int) {
    Square copy(*this);
    numOfAircrafts = numOfAircrafts + 1;
    return copy;
}

Square &Square::operator--() {
    if(numOfAircrafts > 0){
        numOfAircrafts = numOfAircrafts - 1;
    }
    return *this;
}

const Square Square::operator--(int) {
    if(numOfAircrafts > 0){
        Square copy(*this);
        numOfAircrafts = numOfAircrafts - 1;
        return copy;
    }
    return *this;
}

bool operator==(const Square &lhs, const Square &rhs) {
    return ( (lhs.Coordinates == rhs.Coordinates) && (lhs.numOfAircrafts == rhs.numOfAircrafts) );
}

bool operator!=(const Square &lhs, const Square &rhs) {
    return !( (lhs.Coordinates == rhs.Coordinates) && (lhs.numOfAircrafts == rhs.numOfAircrafts) );
}


















