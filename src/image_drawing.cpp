#include <iostream>
#include <string>
#include "image_menu.h"
#include "PPM.h"
#include <cmath>
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

void diagonalQuadPattern( ActionData& action_data ) {
    int height = getInteger( action_data, "Image height? ");
    int width = getInteger( action_data, "Image width? ");

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(255);

    for( int row = 0; row < (height-1) / 2; row++ ) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel(row, column, 0, 0);
        }
    }

    for( int row = height / 2; row < height; row++) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel(row, column, 0, 255);
        }
    }

    for ( int row = 0; row < height; row++ ) {
        for ( int column = 0; column < (width-1) / 2; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 2, 0);
        }
    }

    for ( int row = 0; row < height; row++ ) {
        for ( int column = width / 2; column < width; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 2, 255);
        }
    }

    for ( int row = 0; row < height; row++ ) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 1, ( 2*row + 2*column ) % 256);
        }
    }
}

void stripedDiagonalPattern( ActionData& action_data ) {
    int height = getInteger( action_data, "Image height? ");
    int width = getInteger( action_data, "Image width? ");

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);

    int MaxColorValue = (height + width) / 3;

    if ( MaxColorValue > 255 ) {
        MaxColorValue = 255;
    }
    action_data.getInputImage1().setMaxColorValue(MaxColorValue);

    for( int row = 0; row < height / 2; row++ ) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel(row, column, 0, 0);
        }
    }

    for( int row = height / 2; row < height; row++) {
        for ( int column = 0; column < width; column++ ) {
            if( row % 3 == 0 ) {
                action_data.getInputImage1().setChannel(row, column, 0, 0);
            } else {
                action_data.getInputImage1().setChannel(row, column, 0, MaxColorValue);
            }
        }
    }

    for ( int row = 0; row < height; row++ ) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 1, ( (row + width - column - 1) % (1+MaxColorValue) ) );

            if( (column < row) ) {
                action_data.getInputImage1().setChannel( row, column, 2, 0 );
            } else {
                action_data.getInputImage1().setChannel( row, column, 2, MaxColorValue );
            }
        }
    }
}

// PRACTICE EXAM 9/13/2023
void simpleSquaresPattern( ActionData& action_data ) {
    // Asks the user for an integer with “Image size? “. Configures the Image’s height and width using this size. Sets the red channels in the top half of the image to 127. The bottom half of the image will have red set to 255. The left half of the image will have green channels set to 0. The right half will have green channels set to 255. All blue channels will be set to 255.

    int size = getInteger( action_data, "Image size? ");
    action_data.getInputImage1().setHeight(size);
    action_data.getInputImage1().setWidth(size);

    int height = action_data.getInputImage1().getHeight();
    int width = action_data.getInputImage1().getWidth();

    // RED
    for( int row = 0; row < (height) / 2; row++ ) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel(row, column, 0, 127);
        }
    }

    // RED
    for( int row = height / 2; row < height; row++) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel(row, column, 0, 255);
        }
    }

    // GREEN
    for ( int row = 0; row < height; row++ ) {
        for ( int column = 0; column < (width) / 2; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 1, 0);
        }
    }

    // GREEN
    for ( int row = 0; row < height; row++ ) {
        for ( int column = width / 2; column < width; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 1, 255);
        }
    }

    // BLUE
    for ( int row = 0; row < height; row++ ) {
        for ( int column = 0; column < width; column++ ) {
            action_data.getInputImage1().setChannel( row, column, 2, 255);
        }
    }

}

// EXAM 9/15/2023

void flagRomaniaPattern( ActionData& action_data ) {
    int height = getInteger( action_data, "Image height? ");
    int width = (height*3)/2;

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);

    int MaxColorValue = 255;

    action_data.getInputImage1().setMaxColorValue(MaxColorValue);

    for( int row = 0; row < height; row++) {
        for( int column = 0; column < width; column++ ) {

            int left_third = width/3;
            int middle_third = left_third+left_third;

            if (column < left_third) {
                action_data.getInputImage1().setPixel(row, column, 0, 43, 127);
            }

            if ( (column > left_third) && (column < middle_third)) {
                action_data.getInputImage1().setPixel(row, column, 252, 209, 22);
            }

            if ( (column > middle_third)) {
                action_data.getInputImage1().setPixel(row, column, 206, 17, 38);
            }
        }
    }
}

// Assignment 4: Continuing Assignments

void setSize( ActionData& action_data ) {
    int height = getInteger( action_data, "Height? ");
    int width = getInteger( action_data, "Width? ");

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ) {
    int maxColorValue = getInteger( action_data, "Max color value? ");

    action_data.getInputImage1().setMaxColorValue(maxColorValue);
}

void setChannel( ActionData& action_data ) {
    int row = getInteger( action_data, "Row? ");
    int column = getInteger( action_data, "Column? ");
    int channel = getInteger( action_data, "Channel? ");
    int value =  getInteger( action_data, "Value? ");

    action_data.getInputImage1().setChannel(row, column, channel, value);
}

void setPixel( ActionData& action_data ) {
    int row = getInteger( action_data, "Row? ");
    int column = getInteger( action_data, "Column? ");
    int red = getInteger( action_data, "Red? ");
    int green =  getInteger( action_data, "Green? ");
    int blue =  getInteger( action_data, "Blue? ");

    action_data.getInputImage1().setPixel(row, column, red, green, blue);
}

void clearAll( ActionData& action_data ) {
    for( int column = 0; column <= action_data.getInputImage1().getWidth(); column++ ) {
        for( int row = 0; row <= action_data.getInputImage1().getHeight(); row++ ) {
            action_data.getInputImage1().setPixel(row, column, 0, 0, 0);
        }
    }
}

void drawCircle(ActionData& action_data) {
    int row = getInteger(action_data, "Center Row? ");
    int column = getInteger(action_data, "Center Column? ");
    int radius = getInteger(action_data, "Radius? ");
    int R = getInteger(action_data, "Red? ");
    int G = getInteger(action_data, "Green? ");
    int B = getInteger(action_data, "Blue? ");

    for( int row_ = row-radius; row_ <= row+radius; row_++) { 
        for( int column_ = column-radius; column_ <= column+radius; column_++) {
            int row_difference = (row - row_)*(row - row_);
            int column_difference = (column - column_)*(column - column_);
            double distance = sqrt(row_difference + column_difference);
            
            if( (0 <= distance) && (distance <= radius) ) {
                action_data.getInputImage1().setPixel(row_, column_, R, G, B);
            }
        }
    }
}

void drawBox(ActionData& action_data) {
    int row_top = getInteger(action_data, "Top Row? ");
    int column_left = getInteger(action_data, "Left Column? ");
    int row_bottom = getInteger(action_data, "Bottom Row? ");
    int column_right = getInteger(action_data, "Right Column? ");
    int R = getInteger(action_data, "Red? ");
    int G = getInteger(action_data, "Green? ");
    int B = getInteger(action_data, "Blue? ");

    for( int row = row_top; row <= row_bottom; row++) { 
        for( int column = column_left; column <= column_right; column++) {
            action_data.getInputImage1().setPixel(row, column, R, G, B);
        }
    }
}

// PRACTICE EXAM 10/06/23

void drawTestColorPattern(ActionData& action_data) {
    int height = getInteger( action_data, "Height? ");
    int width = getInteger( action_data, "Width? ");
    int max = getInteger( action_data, "Max color value? ");

    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(max);

    for( int row = 0; row < (height/2); row++ ) { // TOP LEFT
        for( int column = 0; column < (width/2); column++ ) {
            int R = max;
            int G = 0;
            int B = 0;
            action_data.getInputImage1().setPixel(row, column, R, G, B);
        }
    }

    for( int row = 0; row < (height/2); row++ ) { // TOP RIGHT
        for( int column = (width/2); column < width; column++ ) {
            int R = 0;
            int G = max;
            int B = 0;
            action_data.getInputImage1().setPixel(row, column, R, G, B);
        }
    }

    for( int row = (height/2); row < height; row++ ) { // BOTTOM LEFT
        for( int column = 0; column < (width/2); column++ ) {
            int R = 0;
            int G = 0;
            int B = max;
            action_data.getInputImage1().setPixel(row, column, R, G, B);
        }
    }

    for( int row = (height/2); row < height; row++ ) { // BOTTOM RIGHT
        for( int column = (width/2); column < width; column++ ) {
            int R = max/2;
            int G = max/2;
            int B = max/2;
            action_data.getInputImage1().setPixel(row, column, R, G, B);
        }
    }
}

// EXAM 2 10/09/23

void drawSquare(ActionData& action_data) {
    int row = getInteger( action_data, "Row? ");
    int column = getInteger(action_data, "Column? ");
    int size = getInteger(action_data, "Size? ");
    int R = getInteger(action_data, "Red? ");
    int G = getInteger(action_data, "Green? ");
    int B = getInteger(action_data, "Blue? ");

    for( int row_ = (row-(size/2)); row_ <= (row+(size/2)); row_++) { 
        for( int column_ = (column-(size/2)); column_ <= (column+(size/2)); column_++) {
            action_data.getInputImage1().setPixel(row_, column_, R, G, B);
        }
    }
}

// AFTER EXAM 2

void configureGrid(ActionData& action_data) {
    int height = getInteger( action_data, "Grid Height? ");
    int width = getInteger( action_data, "Grid Width? ");
    int max = getInteger( action_data, "Grid Max Value? ");

    action_data.getGrid().setGridSize(height, width);
    action_data.getGrid().setMaxNumber(max);
}

void setGrid(ActionData& action_data) {
    int row = getInteger( action_data, "Grid Row? ");
    int column = getInteger(action_data, "Grid Column? ");
    int value = getInteger(action_data, "Grid Value? ");

    action_data.getGrid().setNumber(row, column, value);
}

void applyGrid(ActionData& action_data) {
    action_data.getGrid().setPPM( action_data.getOutputImage() );
}

void setColorTableSize(ActionData& action_data) {
    int size = getInteger( action_data, "Size? ");
    action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData& action_data) {
    int position = getInteger( action_data, "Position? ");
    int red = getInteger( action_data, "Red? ");
    int green = getInteger( action_data, "Green? ");
    int blue = getInteger( action_data, "Blue? ");

    action_data.getTable()[position].setRed(red);
    action_data.getTable()[position].setGreen(green);
    action_data.getTable()[position].setBlue(blue);
}

void setRandomColor(ActionData& action_data) {
    int position = getInteger( action_data, "Position? ");

    action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData& action_data) {
    int position1 = getInteger( action_data, "First position? ");
    int red1 = getInteger( action_data, "First red? ");
    int green1 = getInteger( action_data, "First green? ");
    int blue1 = getInteger( action_data, "First blue? ");
    int position2 = getInteger( action_data, "Second position? ");
    int red2 = getInteger( action_data, "Second red? ");
    int green2 = getInteger( action_data, "Second green? ");
    int blue2 = getInteger( action_data, "Second blue? ");

    Color color1(red1, green1, blue1);
    Color color2(red2, green2, blue2);

    action_data.getTable().insertGradient(color1, color2, position1, position2);
}

void applyGridColorTable(ActionData& action_data) {
    action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}

void setFractalPlaneSize(ActionData& action_data) {
    // DYNAMIC_CAST
    //action_data.getGrid();
    ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double minx = getDouble( action_data, "Min X? ");
        double maxx = getDouble( action_data, "Max X? ");
        double miny = getDouble( action_data, "Min Y? ");
        double maxy = getDouble( action_data, "Max Y? ");

        object_->setPlaneSize(minx, maxx, miny, maxy);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
    }
}

void calculateFractal(ActionData& action_data) {
    action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData& action_data) {

    JuliaSet* object_ = dynamic_cast<JuliaSet*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double A = getDouble( action_data, "Parameter a? ");
        double B = getDouble( action_data, "Parameter b? ");

        object_->setParameters(A, B);
    } else {
        action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
    }
}

// PRACTICE EXAM 3 11/06/23

void setMandelbrotPower(ActionData& action_data) {

    MandelbrotPower* object_ = dynamic_cast<MandelbrotPower*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double power = getDouble( action_data, "Power? ");
        object_->setPower(power);
    } else {
        action_data.getOS() << "Not a MandelbrotPower object. Can’t set power." << std::endl;
    }
}

void zoomPlane(ActionData& action_data) {
    ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double zoomFactor = getDouble( action_data, "Zoom Factor? ");

        object_->zoomPlane(zoomFactor);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can’t zoom plane." << std::endl;
    }
}


// EXAM 3 11/08/23

void panPlaneRight(ActionData& action_data) {
    ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double panFactor = 0.1;

        object_->panPlaneRight(panFactor);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can’t pan plane." << std::endl;
    }
}

void panPlaneLeft(ActionData& action_data) {
    ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double panFactor = 0.1;

        object_->panPlaneLeft(panFactor);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can’t pan plane." << std::endl;
    }
}

void panPlaneUp(ActionData& action_data) {
    ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double panFactor = 0.1;

        object_->panPlaneUp(panFactor);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can’t pan plane." << std::endl;
    }
}

void panPlaneDown(ActionData& action_data) {
    ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    
    if(object_ != 0) {
        double panFactor = 0.1;

        object_->panPlaneDown(panFactor);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can’t pan plane." << std::endl;
    }
}

void calculateFractalSingleThread(ActionData& action_data) {
    NumberGrid* object_ = dynamic_cast<NumberGrid*>(&action_data.getGrid());
    
    if(object_ != 0) {
        object_->calculateAllNumbers();
    }
}

