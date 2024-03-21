#include <iostream>
#include <string>
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "ThreadedGrid.h"
#include <cmath>

ComplexFractal::ComplexFractal( )
    : ThreadedGrid(201, 301), mMinX(-1.5), mMinY(-1), mMaxX(1.5), mMaxY(1), mDeltaX(0.01), mDeltaY(0.01) {
        
}

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ThreadedGrid(height, width), mMinX(min_x), mMinY(min_y), mMaxX(max_x), mMaxY(max_y) {
    setDeltas(calculateDeltaX(), calculateDeltaY());
}

ComplexFractal::~ComplexFractal( ) {
    
}

double ComplexFractal::getMinX( ) const {
    return mMinX;
}

double ComplexFractal::getMaxX( ) const {
    return mMaxX;
}

double ComplexFractal::getMinY( ) const {
    return mMinY;
}

double ComplexFractal::getMaxY( ) const {
    return mMaxY;
}

void ComplexFractal::setGridSize( const int& height, const int& width ) {
    if( (height >= 2) && (width >= 2) ) {
        int height1 = ThreadedGrid::getHeight();
        int width1 = ThreadedGrid::getWidth();
        ThreadedGrid::setGridSize(height, width);

        if( (height1 != height) || (width1 != width) ) {
            setDeltas(calculateDeltaX(), calculateDeltaY());
        }
    }
}

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    if( ( (-2.0 <= min_x) && (min_x <= 2.0) ) && ( (-2.0 <= max_x) && (max_x <= 2.0) ) && ( (-2.0 <= min_y) && (min_y <= 2.0) ) && ( (-2.0 <= max_y) && (max_y <= 2.0) ) ) {
        double x1 = getMinX();
        double x2 = getMaxX();
        double y1 = getMinY();
        double y2 = getMaxY();

        if( (min_x == max_x) ) {
            return;
        }

        if( (min_y == max_y) ) {
            return;
        }

        if( x1 != min_x ) {
            mMinX = min_x;

            double delta_x = calculateDeltaX();
            double delta_y = calculateDeltaY();
            setDeltas( delta_x, delta_y);
        }

        if( x2 != max_x ) {
            mMaxX = max_x;

            double delta_x = calculateDeltaX();
            double delta_y = calculateDeltaY();
            setDeltas( delta_x, delta_y);
        }

        if( y1 != min_y ) {
            mMinY = min_y;

            double delta_x = calculateDeltaX();
            double delta_y = calculateDeltaY();
            setDeltas( delta_x, delta_y);
        }

        if( y2 != max_y ) {
            mMaxY = max_y;

            double delta_x = calculateDeltaX();
            double delta_y = calculateDeltaY();
            setDeltas( delta_x, delta_y);
        }

        if( mMinX > mMaxX) {
            double val1 = mMinX;
            double val2 = mMaxX;
            mMinX = val2;
            mMaxX = val1;

            double delta_x = calculateDeltaX();
            double delta_y = calculateDeltaY();
            setDeltas( delta_x, delta_y);
        }

        if( mMinY > mMaxY ) {
            double val1 = mMinY;
            double val2 = mMaxY;
            mMinY = val2;
            mMaxY = val1;

            double delta_x = calculateDeltaX();
            double delta_y = calculateDeltaY();
            setDeltas( delta_x, delta_y);
        }
    }
}

double ComplexFractal::getDeltaX( ) const {
    return mDeltaX;
}

double ComplexFractal::getDeltaY( ) const {
    return mDeltaY;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
    if( (delta_x > 0.0) && (delta_y > 0.0) ) {
        mDeltaX = delta_x;
        mDeltaY = delta_y;
    }
}

double ComplexFractal::calculateDeltaY( ) const {
    double delta_y = (mMaxY - mMinY) / (ThreadedGrid::getHeight() - 1);
    return delta_y;
}

double ComplexFractal::calculateDeltaX( ) const {
    double delta_x = (mMaxX - mMinX) / (ThreadedGrid::getWidth() - 1);
    return delta_x;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column) const {
    if( (column < 0) || (column >= getWidth()) ) {
        return 0.0;
    }

    double plane_x = mMinX + column * mDeltaX;
    return plane_x;
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if( (row < 0) || (row >= getHeight()) ) {
        return 0.0;
    }

    double plane_y = mMaxY - row * mDeltaY;
    return plane_y;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
    double plane_x = calculatePlaneXFromPixelColumn(column);
    double plane_y = calculatePlaneYFromPixelRow(row);
    
    if( (row < 0) || (row >= getHeight()) || (column < 0) || (column >= getWidth())) {
        x = 0;
        y = 0;
    } else {
        x = plane_x;
        y = plane_y;
    }
}

int ComplexFractal::calculateNumber( const int& row, const int& column ) const {
    if( (0 <= column) && (column < getWidth()) && (0 <= row) && (row < getHeight()) ) {
        double x;
        double y;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        int value = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
        return value;
    }

    return -1;
}

// PRACTICE EXAM 3 11/06/23

void ComplexFractal::zoomPlane(const double& zoom_factor) {
    double x_difference = mMaxX - mMinX;
    double x_desired = x_difference*zoom_factor;
    double x_change = (x_difference-x_desired)/2;

    double y_difference = mMaxY - mMinY;
    double y_desired = y_difference*zoom_factor;
    double y_change = (y_difference-y_desired)/2;

    double min_x = mMinX + x_change;

    if(min_x < -2.0) {
        min_x = -2.0;
    }

    double max_x = mMaxX - x_change;

    if(max_x > 2.0) {
        max_x = 2.0;
    }

    double min_y = mMinY + y_change;

    if(min_y < -2.0) {
        min_y = -2.0;
    }

    double max_y = mMaxY - y_change;

    if(max_y > 2.0) {
        max_y = 2.0;
    }

    setPlaneSize(min_x, max_x, min_y, max_y);
}

// EXAM 3 11/08/23

void ComplexFractal::panPlaneRight(const double& pan_factor) {
    double x_size = mMaxX - mMinX;
    double pan_size = x_size*pan_factor;

    double min_x = mMinX + pan_size;
    double max_x = mMaxX + pan_size;

    if( (min_x <= 2.0) or (max_x <= 2.0) ) {
        setPlaneSize(min_x, max_x, mMinY, mMaxY);
    }
}

void ComplexFractal::panPlaneLeft(const double& pan_factor) {
    double x_size = mMaxX - mMinX;
    double pan_size = x_size*pan_factor;

    double min_x = mMinX - pan_size;
    double max_x = mMaxX - pan_size;

    if( (min_x >= -2.0) or (max_x >= -2.0) ) {
        setPlaneSize(min_x, max_x, mMinY, mMaxY);
    }
}

void ComplexFractal::panPlaneUp(const double& pan_factor) {
    double y_size = mMaxY - mMinY;
    double pan_size = y_size*pan_factor;

    double min_y = mMinY + pan_size;
    double max_y = mMaxY + pan_size;

    if( (min_y <= 2.0) or (max_y <= 2.0) ) {
        setPlaneSize(mMinX, mMaxX, min_y, max_y);
    }
}

void ComplexFractal::panPlaneDown(const double& pan_factor) {
    double y_size = mMaxY - mMinY;
    double pan_size = y_size*pan_factor;

    double min_y = mMinY - pan_size;
    double max_y = mMaxY - pan_size;

    if( (min_y >= -2.0) or (max_y >= -2.0) ) {
        setPlaneSize(mMinX, mMaxX, min_y, max_y);
    }
}
