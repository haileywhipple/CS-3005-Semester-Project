#include <iostream>
#include <string>
#include "image_menu.h"
#include "ActionData.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

int assignment1( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);

    return askQuestions3( action_data );
}

int assignment2( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);

    diagonalQuadPattern( action_data );
    copyImage(action_data);
    drawAsciiImage( action_data );

    return 0;
}

int assignment3( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);

    stripedDiagonalPattern( action_data );
    copyImage(action_data);
    writeUserImage( action_data );

    return 0;
}

// PRACTICE EXAM 9/13/2023

int inquisitor( std::istream& is, std::ostream& os ) {
    // calls askInquistorQuestions passing along its parameters. Returns the value returned by askInquisitorQuestions;

    ActionData action_data(is, os);

    return askInquisitorQuestions( action_data );
}

int simple_squares_ascii( std::istream& is, std::ostream& os ) {
    // Creates a default constructed image object. Calls simpleSquaresPattern() to configure the Image object. Calls drawAsciiImage to display the Image object to the user. Returns 0.

    ActionData action_data(is, os);

    simpleSquaresPattern( action_data );
    copyImage(action_data);
    drawAsciiImage( action_data );

    return 0;
}

// EXAM 9/15/2023

int flag_romania( std::istream& is, std::ostream& os ) {

    ActionData action_data(is, os);

    flagRomaniaPattern( action_data );
    copyImage(action_data);
    writeUserImage( action_data );

    return 0;

}

// Assignment 4: Continuing Assignments

void showMenu( MenuData& menu_data, ActionData& action_data ) {
    int s = menu_data.getNames().size();
    for( int i = 0; i < s; i++) {
        std::string name = menu_data.getNames()[i];
        std::string description = menu_data.getDescription(name);
        std::string output = name + ") " + description + "\n";
        action_data.getOS() << output;
    }
}

void takeAction( const std::string& choice, MenuData& menu_data, ActionData& action_data ) {
    // Uses choice as a command name to get a ActionFunctionType from the MenuData. If the function returned is not 0, then call the returned function, passing the ActionData as its parameter. Otherwise, if the choice was “menu”, call showMenu. Otherwise (if the function was 0 and choice was not “menu”), display a message with the format: “Unknown action ‘bad-choice’.”, where bad-choice should be the choice.
    if( menu_data.getFunction(choice) != 0 ) {
        menu_data.getFunction(choice)(action_data);
    } else if ( choice == "menu" ) {
        showMenu(menu_data, action_data);
    } else {
        action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
    }
}

void configureMenu( MenuData& menu_data ) {
    // TABLE OF COMMANDS

    // draw-ascii
    std::string name = "draw-ascii";
    std::string description = "Write output image to terminal as ASCII art.";
    menu_data.addAction(name, drawAsciiImage, description);

    // write
    name = "write";
    description = "Write output image to file.";
    menu_data.addAction(name, writeUserImage, description);

    // copy
    name = "copy";
    description = "Copy input image 1 to output image.";
    menu_data.addAction(name, copyImage, description);

    // read1
    name = "read1";
    description = "Read file into input image 1.";
    menu_data.addAction(name, readUserImage1, description);

    // #
    name = "#";
    description = "Comment to end of line.";
    menu_data.addAction(name, commentLine, description);

    // size
    name = "size";
    description = "Set the size of input image 1.";
    menu_data.addAction(name, setSize, description);

    // max-color-value
    name = "max-color-value";
    description = "Set the max color value of input image 1.";
    menu_data.addAction(name, setMaxColorValue, description);

    // channel
    name = "channel";
    description = "Set a channel value in input image 1.";
    menu_data.addAction(name, setChannel, description);

    // pixel
    name = "pixel";
    description = "Set a pixel's 3 values in input image 1.";
    menu_data.addAction(name, setPixel, description);

    // clear
    name = "clear";
    description = "Set all pixels to 0,0,0 in input image 1.";
    menu_data.addAction(name, clearAll, description);

    // quit
    name = "quit";
    description = "Quit.";
    menu_data.addAction(name, quit, description);

    // read2
    name = "read2";
    description = "Read file into input image 2.";
    menu_data.addAction(name, readUserImage2, description);

    // +
    name = "+";
    description = "Set output image from sum of input image 1 and input image 2.";
    menu_data.addAction(name, plus, description);

    // +=
    name = "+=";
    description = "Set input image 1 by adding in input image 2.";
    menu_data.addAction(name, plusEquals, description);

    // -
    name = "-";
    description = "Set output image from difference of input image 1 and input image 2.";
    menu_data.addAction(name, minus, description);

    // -=
    name = "-=";
    description = "Set input image 1 by subtracting input image 2.";
    menu_data.addAction(name, minusEquals, description);

    // *
    name = "*";
    description = "Set output image from input image 1 multiplied by a number.";
    menu_data.addAction(name, times, description);

    // *=
    name = "*=";
    description = "Set input image 1 by multiplying by a number.";
    menu_data.addAction(name, timesEquals, description);

    // /
    name = "/";
    description = "Set output image from input image 1 divided by a number.";
    menu_data.addAction(name, divide, description);

    // /=
    name = "/=";
    description = "Set input image 1 by dividing by a number.";
    menu_data.addAction(name, divideEquals, description);

    // red-gray
    name = "red-gray";
    description = "Set output image by grayscale from red on input image 1.";
    menu_data.addAction(name, grayFromRed, description);

    // green-gray
    name = "green-gray";
    description = "Set output image by grayscale from green on input image 1.";
    menu_data.addAction(name, grayFromGreen, description);

    // blue-gray
    name = "blue-gray";
    description = "Set output image by grayscale from blue on input image 1.";
    menu_data.addAction(name, grayFromBlue, description);

    // linear-gray
    name = "linear-gray";
    description = "Set output image by linear colorimetric grayscale on input image 1.";
    menu_data.addAction(name, grayFromLinearColorimetric, description);

    // circle
    name = "circle";
    description = "Draw a circle shape in input image 1.";
    menu_data.addAction(name, drawCircle, description);

    // box
    name = "box";
    description = "Draw a box shape in input image 1.";
    menu_data.addAction(name, drawBox, description);

    // sepia
    name = "sepia";
    description = "Set output image from sepia filter on input image 1.";
    menu_data.addAction(name, sepiaFilter, description);

    // +=-int
    name = "+=-int";
    description = "Set input image 1 by adding by an integer.";
    menu_data.addAction(name, plusEqualsInt, description);

    // test-pattern
    name = "test-pattern";
    description = "Draw a test pattern in input image 1.";
    menu_data.addAction(name, drawTestColorPattern, description);

    // diagonal-quad
    name = "diagonal-quad";
    description = "Draw a diagonal quad pattern in input image 1.";
    menu_data.addAction(name, diagonalQuadPattern, description);

    // striped-diagonal
    name = "striped-diagonal";
    description = "Draw a striped diagonal pattern in input image 1.";
    menu_data.addAction(name, stripedDiagonalPattern, description);

    // square
    name = "square";
    description = "Draw a square shape in input image 1.";
    menu_data.addAction(name, drawSquare, description);

    // orange
    name = "orange";
    description = "Set output image from orange filter on input image 1.";
    menu_data.addAction(name, orangeFilter, description);


    // grid
    name = "grid";
    description = "Configure the grid.";
    menu_data.addAction(name, configureGrid, description);

    // grid-set
    name = "grid-set";
    description = "Set a single value in the grid.";
    menu_data.addAction(name, setGrid, description);

    // grid-apply
    name = "grid-apply";
    description = "Use the grid values to set colors in the output image.";
    menu_data.addAction(name, applyGrid, description);

    // set-color-table-size
    name = "set-color-table-size";
    description = "Change the number of slots in the color table.";
    menu_data.addAction(name, setColorTableSize, description);

    // set-color
    name = "set-color";
    description = "Set the RGB values for one slot in the color table.";
    menu_data.addAction(name, setColor, description);

    // set-random-color
    name = "set-random-color";
    description = "Randomly set the RGB values for one slot in the color table.";
    menu_data.addAction(name, setRandomColor, description);

    // set-color-gradient
    name = "set-color-gradient";
    description = "Smoothly set the RGB values for a range of slots in the color table.";
    menu_data.addAction(name, setColorGradient, description);

    // grid-apply-color-table
    name = "grid-apply-color-table";
    description = "Use the grid values to set colors in the output image using the color table.";
    menu_data.addAction(name, applyGridColorTable, description);

    // fractal-plane-size
    name = "fractal-plane-size";
    description = "Set the dimensions of the grid in the complex plane.";
    menu_data.addAction(name, setFractalPlaneSize, description);

    // fractal-calculate
    name = "fractal-calculate";
    description = "Calculate the escape values for the fractal.";
    menu_data.addAction(name, calculateFractal, description);

    // julia-parameters
    name = "julia-parameters";
    description = "Set the parameters of the Julia Set function.";
    menu_data.addAction(name, setJuliaParameters, description);

    // complex-fractal
    name = "complex-fractal";
    description = "Choose to make a complex plane.";
    menu_data.addAction(name, setComplexFractal, description);

    // julia
    name = "julia";
    description = "Choose to make a Julia set.";
    menu_data.addAction(name, setJuliaFractal, description);

    // mandelbrot
    name = "mandelbrot";
    description = "Choose to make a Mandelbrot set.";
    menu_data.addAction(name, setMandelbrotFractal, description);

    // mandelbrot-power
    name = "mandelbrot-power";
    description = "Choose to make a Mandelbrot set with the power function.";
    menu_data.addAction(name, setMandelbrotPowerFractal, description);

    // set-mandelbrot-power
    name = "set-mandelbrot-power";
    description = "Choose a power for the Mandelbrot power function.";
    menu_data.addAction(name, setMandelbrotPower, description);

    // fractal-zoom
    name = "fractal-zoom";
    description = "Zoom in or out of the complex plane.";
    menu_data.addAction(name, zoomPlane, description);

    // julia-four
    name = "julia-four";
    description = "Choose to make a Julia set with the fourth power function.";
    menu_data.addAction(name, setJuliaFourFractal, description);

    // fractal-right
    name = "fractal-right";
    description = "Pan complex plane right.";
    menu_data.addAction(name, panPlaneRight, description);

    // fractal-left
    name = "fractal-left";
    description = "Pan complex plane left.";
    menu_data.addAction(name, panPlaneLeft, description);

    // fractal-up
    name = "fractal-up";
    description = "Pan complex plane up.";
    menu_data.addAction(name, panPlaneUp, description);

    // fractal-down
    name = "fractal-down";
    description = "Pan complex plane down.";
    menu_data.addAction(name, panPlaneDown, description);

    // fractal-calculate-single-thread
    name = "fractal-calculate-single-thread";
    description = "Calculate the escape values for the fractal, single-thread.";
    menu_data.addAction(name, calculateFractalSingleThread, description);

    // copyo1
    name = "copyo1";
    description = "Copy output image to input image 1.";
    menu_data.addAction(name, copyOutputImageToImage1, description);

    // anti-alias
    name = "anti-alias";
    description = "Set output image from Anti-alias filter on input image 1.";
    menu_data.addAction(name, antiAliasFilter, description);

    // 
    //name = "";
    //description = "";
    //menu_data.addAction(name, , description);

}

int imageMenu(std::istream& is, std::ostream& os) {
    // Creates an ActionData object with is and os used for its input and output streams. Creates a MenuData object. Uses configureMenu to configure the commands in the MenuData object. Uses a loop that will continue as long as the ActionData object is not “done” and the ActionData object’s input stream is .good(). The body of the loop will use getChoice to get the user’s command choice, and takeAction to execute the user’s command choice. Returns 0.
    ActionData action_data(is, os);
    //ComplexFractal *grid = new ComplexFractal();
    //NumberGrid *grid = new NumberGrid;
    NumberGrid *grid = new ComplexFractal;
    action_data.setGrid(grid);
    MenuData menu_data;
    
    configureMenu(menu_data);

    while ( (action_data.getDone() == false) && (action_data.getIS().good()) ) {
        std::string choice = getChoice( action_data );
        takeAction(choice, menu_data, action_data);
    }

    return 0;
}

void setComplexFractal(ActionData& action_data) {
    NumberGrid *grid = new ComplexFractal;
    action_data.setGrid(grid);
}

void setJuliaFractal(ActionData& action_data) {
    ComplexFractal *grid = new JuliaSet;
    action_data.setGrid(grid);
}

void setMandelbrotFractal( ActionData& action_data ) {
    ComplexFractal *grid = new MandelbrotSet;
    action_data.setGrid(grid);
}

// PRACTICE EXAM 3 11/06/23

void setMandelbrotPowerFractal(ActionData& action_data) {
    MandelbrotSet *grid = new MandelbrotPower;
    action_data.setGrid(grid);
}

// EXAM 3 11/08/23

void setJuliaFourFractal(ActionData& action_data) {
    JuliaSet *grid = new JuliaSetFour;
    action_data.setGrid(grid);
}

