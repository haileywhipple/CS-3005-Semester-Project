#include <iostream>
#include <string>
#include "MandelbrotSet.h"
#include <cmath>

MandelbrotSet::MandelbrotSet()
    : ComplexFractal() {

}

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y) {
    
}

MandelbrotSet::~MandelbrotSet() {
    
}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double& y1 ) const {
    x1 = x0*x0 - y0*y0 + a;
    y1 = 2*x0*y0 + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
    int n = 0;
    int maxNum = getMaxNumber();

    double CENTER_X = 0;
    double CENTER_Y = 0;
    double radius = 2.0;

    double x1 = a;
    double y1 = b;

    while(n < maxNum) {

        double y_difference = (CENTER_Y - y1)*(CENTER_Y - y1);
        double x_difference = (CENTER_X - x1)*(CENTER_X - x1);
        double distance = sqrt(x_difference + y_difference);
                
        if( distance > radius ) {
            return n;
        }

        calculateNextPoint(x1, y1, a, b, x1, y1);
        n += 1;
    }

    return n;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
    if( (0 <= column) && (column < getWidth()) && (0 <= row) && (row < getHeight()) ) {
        double a;
        double b;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, a, b);
        int num = calculatePlaneEscapeCount(a, b);
        return num;
    }

    return -1;
}

// PRACTICE EXAM 3 11/06/23

MandelbrotPower::MandelbrotPower()
    : MandelbrotSet(), mPower(2.0) {

}

MandelbrotPower::~MandelbrotPower() {
    
}

double MandelbrotPower::getPower() const {
    return mPower;
}

void MandelbrotPower::setPower(const double& power) {
    mPower = power;
}

void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
    double r = std::sqrt(x0*x0 + y0*y0);
    double theta = std::atan2(y0, x0);
    x1 = std::pow(r, mPower) * std::cos(mPower * theta) + a;
    y1 = std::pow(r, mPower) * std::sin(mPower * theta) + b;
}

