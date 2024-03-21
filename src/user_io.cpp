#include <iostream>
#include <string>
#include <fstream>
#include "image_menu.h"
#include "ActionData.h"

std::string getString( ActionData& action_data, const std::string& prompt ) {
    std::string result;
    action_data.getOS() << prompt;
    action_data.getIS() >> result;
    return result;
}

int getInteger( ActionData& action_data, const std::string& prompt ) {
    int result;
    action_data.getOS() << prompt;
    action_data.getIS() >> result;
    return result;
}

double getDouble( ActionData& action_data, const std::string& prompt ) {
    double result;
    action_data.getOS() << prompt;
    action_data.getIS() >> result;
    return result;
}

int askQuestions3( ActionData& action_data ) {
    std::string color = getString( action_data, "What is your favorite color? ");
    int integer = getInteger( action_data, "What is your favorite integer? ");
    double number = getDouble( action_data, "What is your favorite number? ");

    if(integer > 0) {
        for (int i = 1; i!=integer+1 ; ++i) {
            action_data.getOS() << i << " " << color << " " << number << std::endl;
        }
    }
    return integer;
}

// PRACTICE EXAM 9/13/2023
int askInquisitorQuestions( ActionData& action_data ) { 
    //Asks the user for a string with “What is your most powerful Pokemon? “. Then asks for an integer with “What is its level? “. Next asks the user for a double with “What is its health? “. Sends a message to the output formatted as shown above. Returns the pokemon’s level.

    std::string pokemon = getString( action_data, "What is your most powerful Pokemon? ");
    int level = getInteger( action_data, "What is its level? ");
    double health = getDouble( action_data, "What is its health? ");
    action_data.getOS() << pokemon << " is level " << level << " and " << health << " HP." << std::endl;

    return level;
}

// Assignment 4: Continuing Assignments

std::string getChoice( ActionData& action_data ) {
    std::string choice = getString( action_data, "Choice? " );
    return choice;
}

void commentLine( ActionData& action_data ) {
    // ./unit-test.bash 05

    // Uses .read() to read a single character at a time from the input stream. If the input stream is .good() after the read, and if the character read is not the newline character, repeat. Otherwise return. In other words, read from the input stream until the input stream has nothing to read, or a newline character is read. Do not do anything with the characters read.

    char c;
    while(!action_data.getIS().eof()) {
        action_data.getIS().read( (char *) &c, 1);
        if( (action_data.getIS().good() == false) || (c == '\n') ) {
            return;
        }
    }
}

void quit(ActionData& action_data) {
    action_data.setDone();
}