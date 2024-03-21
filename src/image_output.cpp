#include <iostream>
#include <string>
#include "image_menu.h"
#include "PPM.h"
#include "ActionData.h"
#include <fstream>

void drawAsciiImage( ActionData& action_data ) {

    int height = action_data.getOutputImage().getHeight();
    int width = action_data.getOutputImage().getWidth();

    for( int row = 0; row < height; row++) {
        for( int column = 0; column < width; column++) {
            int R = action_data.getOutputImage().getChannel(row, column, 0);
            int G = action_data.getOutputImage().getChannel(row, column, 1);
            int B = action_data.getOutputImage().getChannel(row, column, 2);

            double strength = (R+G+B)/765.0;
            std::string symbol;

            if ( strength >= 1.0 ) {
                symbol = '@';
            } else if ( strength >= 0.9 ) {
                symbol = '#';
            } else if ( strength >= 0.8 ) {
                symbol = '%';
            } else if ( strength >= 0.7 ) {
                symbol = '*';
            } else if ( strength >= 0.6 ) {
                symbol = '|';
            } else if ( strength >= 0.5 ) {
                symbol = '+';
            } else if ( strength >= 0.4 ) {
                symbol = ';';
            } else if ( strength >= 0.3 ) {
                symbol = '~';
            } else if ( strength >= 0.2 ) {
                symbol = '-';
            } else if ( strength >= 0.1 ) {
                symbol = '.';
            } else if ( strength >= 0.0 ) {
                symbol = ' ';
            }

            action_data.getOS() << symbol;
        }
        action_data.getOS() << std::endl;
    }
}

void writeUserImage( ActionData& action_data ) {
    std::string filename = getString( action_data, "Output filename? ");

    std::ofstream data_file(filename, std::ios::binary);
    action_data.getOutputImage().writeStream(data_file);

    data_file.close();
}

void copyImage( ActionData& action_data ) {
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data ) {
    std::string name = getString( action_data, "Input filename? ");

    std::fstream file(name);
    if (file.is_open()) {
        action_data.getInputImage1().readStream( file );
        file.close();
    } else {
        action_data.getOS() << "'" << name << "'" << " could not be opened." << std::endl;
    }
}

void readUserImage2( ActionData& action_data ) {
    std::string name = getString( action_data, "Input filename? ");

    std::fstream file(name);
    if (file.is_open()) {
        action_data.getInputImage2().readStream( file );
        file.close();
    } else {
        action_data.getOS() << "'" << name << "'" << " could not be opened." << std::endl;
    }
}

// FINAL EXAM 12/13/23

void copyOutputImageToImage1(ActionData& action_data) {
    action_data.getInputImage1() = action_data.getOutputImage();
}