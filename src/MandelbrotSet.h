#include <iostream>
#include <string>
#include "ComplexFractal.h"

#ifndef _MANDELBROT_SET_H_
#define _MANDELBROT_SET_H_

class MandelbrotSet: public ComplexFractal {
    public:
        MandelbrotSet();
        MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y );
        virtual ~MandelbrotSet();
        virtual void calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double& y1 ) const;
        int calculatePlaneEscapeCount( const double& a, const double& b ) const;
        virtual int calculateNumber( const int& row, const int& column ) const;
};

// PRACTICE EXAM 3 11/06/23

class MandelbrotPower: public MandelbrotSet {
    public:
        MandelbrotPower();
        virtual ~MandelbrotPower();
        double getPower() const;
        void setPower(const double& power);
        virtual void calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const;

    protected:
        double mPower;
};

#endif // _MANDELBROT_SET_H_