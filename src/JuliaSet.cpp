#include <iostream>
#include <string>
#include "JuliaSet.h"
#include "ComplexFractal.h"
#include "NumberGrid.h"
#include <cmath>

JuliaSet::JuliaSet()
    : ComplexFractal(), mA(-0.650492), mB(-0.478235) {
    setMaxNumber(255);
}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b ) 
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b) {
    
}

JuliaSet::~JuliaSet() {
    
}

double JuliaSet::getA() const {
    return mA;
}

double JuliaSet::getB() const {
    return mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {
    if( (-2.0 <= a) && (a <= 2.0) && (-2.0 <= b) && (b <= 2.0) ) {
        mA = a;
        mB = b;
    }
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double& y1 ) const {
    x1 = x0*x0 - y0*y0 + mA;
    y1 = 2*x0*y0 + mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
    int n = 0;
    int maxNum = getMaxNumber();

    double CENTER_X = 0;
    double CENTER_Y = 0;
    double radius = 2.0;

    double y_difference = (CENTER_Y - y0)*(CENTER_Y - y0);
    double x_difference = (CENTER_X - x0)*(CENTER_X - x0);
    double distance = sqrt(x_difference + y_difference);
            
    if( distance > radius ) {
        return n;
    }

    double x1 = x0;
    double y1 = y0;

    while(n < maxNum) {

        double y_difference = (CENTER_Y - y1)*(CENTER_Y - y1);
        double x_difference = (CENTER_X - x1)*(CENTER_X - x1);
        double distance = sqrt(x_difference + y_difference);
                
        if( distance > radius ) {
            return n;
        }

        calculateNextPoint(x1, y1, x1, y1);
        n += 1;
    }

    return n;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const {
    if( (0 <= column) && (column < getWidth()) && (0 <= row) && (row < getHeight()) ) {
        double x;
        double y;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        int num = calculatePlaneEscapeCount(x, y);
        return num;
    }

    return -1;
}

// EXAM 3 11/08/23

JuliaSetFour::JuliaSetFour()
    : JuliaSet() {

}

JuliaSetFour::~JuliaSetFour() {
    
}

void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const {
    x1 = (x0*x0*x0*x0) - 6*(x0*x0)*(y0*y0) + (y0*y0*y0*y0) + mA;
    y1 = 4*(x0*x0*x0)*(y0) - 4*x0*(y0*y0*y0) + mB;
}



