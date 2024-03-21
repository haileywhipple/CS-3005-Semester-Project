#include <iostream>
#include <string>
#include "ColorTable.h"

#include <cstdlib>
#include <ctime>

Color::Color( )
    : mRed(0), mGreen(0), mBlue(0) {

}

Color::Color( const int& red, const int& green, const int& blue )
    : mRed(red), mGreen(green), mBlue(blue) {

}

int Color::getRed( ) const {
    return mRed;
}

int Color::getGreen( ) const {
    return mGreen;
}

int Color::getBlue( ) const {
    return mBlue;
}

int Color::getChannel( const int& channel) const {
    if( channel == 0 ) {
        return mRed;
    } else if( channel == 1) {
        return mGreen;
    } else if( channel == 2) {
        return mBlue;
    } else {
        return -1;
    }
}

void Color::setRed( const int& value ) {
    if( value >= 0 ) {
        mRed = value;
    }
}

void Color::setGreen( const int& value ) {
    if( value >= 0 ) {
        mGreen = value;
    }
}

void Color::setBlue( const int& value ) {
    if( value >= 0 ) {
        mBlue = value;
    }
}

void Color::setChannel( const int& channel, const int& value ) {
    if( value >= 0 ) {
        if( channel == 0 ) {
            mRed = value;
        } else if( channel == 1) {
            mGreen = value;
        } else if( channel == 2) {
            mBlue = value;
        }
    }
}

void Color::invert( const int& max_color_value ) {
    if( mRed > max_color_value ) {
        return;
    }

    if( mGreen >  max_color_value ) {
        return;
    }

    if( mBlue > max_color_value ) {
        return;
    }

    int red = max_color_value - mRed;
    int green = max_color_value - mGreen;
    int blue = max_color_value - mBlue;

    mRed = red;
    mGreen = green;
    mBlue = blue;
}
        
bool Color::operator==( const Color& rhs ) const {
    if( (this->getRed() == rhs.getRed()) && (this->getGreen() == rhs.getGreen()) && (this->getBlue() == rhs.getBlue()) ) {
        return true;
    }
    return false;
}




std::ostream& operator<<( std::ostream& os, const Color& color ) {
    os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
    return os;
}




ColorTable::ColorTable( const int& num_color ) {
    mColors.resize(num_color);
}

int ColorTable::getNumberOfColors( ) const {
    return mColors.size();
}

void ColorTable::setNumberOfColors( const int& num_color ) {
    mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const {
    int size = mColors.size();
    
    if( (i >= 0) && (i < size) ) {
        return mColors[i];
    }
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    return c;
}

Color& ColorTable::operator[]( const int& i ) {
    int size = mColors.size();
    
    if( (i >= 0) && (i < size) ) {
        return mColors[i];
    }
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    return c;
}

void ColorTable::setRandomColor( const int& max_color_value, const int& position ) {
    int size = mColors.size();
    
    if( (0 <= position) && (position < size) && (max_color_value >= 0) ) {
        int value = std::rand() % (max_color_value+1);
        mColors[position].setRed(value);
        value = std::rand() % (max_color_value+1);
        mColors[position].setGreen(value);
        value = std::rand() % (max_color_value+1);
        mColors[position].setBlue(value);
    }
}

double ColorTable::gradientSlope( const double y1, const double y2, const double x1, const double x2 ) const {
    double rise = y2-y1;
    double run = x2-x1;
    double slope = rise/run;
    return slope;
}

double ColorTable::gradientValue( const double y1, const double x1, const double slope, const double x ) const {
    double value = slope * (x-x1) + y1;
    return value;
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 ) {
    int size = mColors.size();
    
    double redSlope = gradientSlope( color1.getRed(), color2.getRed(), position1, position2);
    double greenSlope = gradientSlope( color1.getGreen(), color2.getGreen(), position1, position2);
    double blueSlope = gradientSlope( color1.getBlue(), color2.getBlue(), position1, position2);

    if( (position1 >= 0) && (position2 < size) ) {
        for( int x = position1; x <= position2; x++ ) {
            double redValue = gradientValue(color1.getRed(), position1, redSlope, x);
            double greenValue = gradientValue(color1.getGreen(), position1, greenSlope, x);
            double blueValue = gradientValue(color1.getBlue(), position1, blueSlope, x);

            mColors[x].setRed(redValue);
            mColors[x].setGreen(greenValue);
            mColors[x].setBlue(blueValue);
        }
    }
}

int ColorTable::getMaxChannelValue( ) const {
    int max = mColors[0].getRed();

    int size = mColors.size();

    for( int x = 0; x < size; x++) {
        if( mColors[x].getRed() > max ) {
            max = mColors[x].getRed();
        }

        if( mColors[x].getGreen() > max ) {
            max = mColors[x].getGreen();
        }

        if( mColors[x].getBlue() > max ) {
            max = mColors[x].getBlue();
        }
    }
    
    return max;
}