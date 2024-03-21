#include <iostream>
#include <string>
#include <vector>
#include "NumberGrid.h"
#include "ColorTable.h"

NumberGrid::NumberGrid( )
    : mHeight(300), mWidth(400), mMaximumNumber(255) {
    mGridNumbers.resize(mHeight * mWidth);

    int size = mGridNumbers.size();

    for( int i = 0; i < size; i++) {
        mGridNumbers[i] = 0;
    }
}

NumberGrid::NumberGrid( const int& height, const int& width )
    : mHeight( height ), mWidth( width ), mMaximumNumber( 255 ) {
    mGridNumbers.resize(mHeight * mWidth);

    int size = mGridNumbers.size();

    for( int i = 0; i < size; i++) {
        mGridNumbers[i] = 0;
    }
}

NumberGrid::~NumberGrid() {

}

int NumberGrid::getHeight() const {
    return mHeight;
}

int NumberGrid::getWidth() const {
    return mWidth;
}

int NumberGrid::getMaxNumber() const {
    return mMaximumNumber;
}

void NumberGrid::setGridSize( const int& height, const int& width ) {
    if( (height > 1) && (width > 1) ) {
        mHeight = height;
        mWidth = width;
        mGridNumbers.resize( height*width );
    }
}

void NumberGrid::setMaxNumber( const int& number ) {
    if( number >= 0 ) {
        mMaximumNumber = number;

        for( int i = 0; i < mHeight*mWidth; i++ ) {
            int value = mGridNumbers[i];
            if( value > mMaximumNumber ) {
                mGridNumbers[i] = 0;
            }
        }
    }
}

const std::vector< int >& NumberGrid::getNumbers( ) const {
    return mGridNumbers;
}

int NumberGrid::index( const int& row, const int& column ) const {
    int index = (row * mWidth) + column;
    
    return index;
}

bool NumberGrid::indexValid( const int& row, const int& column ) const {
    if( (0 <= row) && (0 <= column) && (row < mHeight) && (column < mWidth) ) {
        return true;
    } else {
        return false;
    }
}

bool NumberGrid::numberValid( const int& number ) const {
    if( (number >= 0) && (number <= mMaximumNumber) ) {
        return true;
    }
    return false;
}

int NumberGrid::getNumber( const int& row, const int& column ) const {
    if( indexValid(row, column) ) {
        return mGridNumbers[index(row, column)];
    }
    return -1;
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number ) {
    if( indexValid(row, column) ) {
        if( numberValid(number) ) {
            int i = index(row, column);
            mGridNumbers[i] = number;
        }
    }
}

void NumberGrid::setPPM( PPM& ppm ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    ppm.setHeight(height);
    ppm.setWidth(width);
    ppm.setMaxColorValue(63);

    for( int row = 0; row < height; row++ ) {
        for( int column = 0; column < width; column++ ) {
            int number = this->getNumber( row, column );
            
            if( number == 0 ) {
                ppm.setPixel(row, column, 0, 0, 0);
            } else if( number == mMaximumNumber ) {
                ppm.setPixel(row, column, 63, 31, 31);
            } else if( number % 8 == 0 ) {
                ppm.setPixel(row, column, 63, 63, 63);
            } else if( number % 8 == 1 ) {
                ppm.setPixel(row, column, 63, 31, 31);
            } else if( number % 8 == 2 ) {
                ppm.setPixel(row, column, 63, 63, 31);
            } else if( number % 8 == 3 ) {
                ppm.setPixel(row, column, 31, 63, 31);
            } else if( number % 8 == 4 ) {
                ppm.setPixel(row, column, 0, 0, 0);
            } else if( number % 8 == 5 ) {
                ppm.setPixel(row, column, 31, 63, 63);
            } else if( number % 8 == 6 ) {
                ppm.setPixel(row, column, 31, 31, 63);
            } else if( number % 8 == 7 ) {
                ppm.setPixel(row, column, 63, 31, 63);
            }
        }
    }
}

void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const {
    int height = this->getHeight();
    int width = this->getWidth();

    if( colors.getNumberOfColors() < 2 ) {
        return;
    }

    ppm.setHeight(height);
    ppm.setWidth(width);
    ppm.setMaxColorValue(colors.getMaxChannelValue());

    for( int column = 0; column < width; column++ ) {
        for( int row = 0; row < height; row++ ) {
            int number = this->getNumber(row, column);

            if( number == this->getMaxNumber() ) {
                number = colors.getNumberOfColors()-1;
            } else {
                number = number % colors.getNumberOfColors();
            }

            int red = colors[number].getRed();
            int green = colors[number].getGreen();
            int blue = colors[number].getBlue();
            ppm.setPixel(row, column, red, green, blue);
        }
    }
}

void NumberGrid::calculateAllNumbers() {
    int height = this->getHeight();
    int width = this->getWidth();

    for( int column = 0; column < width; column++ ) {
        for( int row = 0; row < height; row++ ) {
            int num = this->calculateNumber(row, column); //???
            this->setNumber(row, column, num);
        }
    }
}

