#include <iostream>
#include <string>
#include <vector>
#include "ActionData.h"
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

ActionData::ActionData(std::istream& is, std::ostream& os)
    : mIS(is), mOS(os), mQuit(false), mNumberGridPointer(0), mColorTable(16) {
    Color color1(0, 255, 0);
    Color color2(255, 0, 255);
    mColorTable.insertGradient(color1, color2, 0, mColorTable.getNumberOfColors()-1);
}

std::istream& ActionData::getIS() {
    return mIS;
}

std::ostream& ActionData::getOS() {
    return mOS;
}

PPM& ActionData::getInputImage1() {
    return mInputImage1;
}

PPM& ActionData::getInputImage2() {
    return mInputImage2;
}

PPM& ActionData::getOutputImage() {
    return mOutputImage;
}

bool ActionData::getDone() const {
    return mQuit;
}

void ActionData::setDone() {
    mQuit = true;
}

ActionData::~ActionData() {
    if(mNumberGridPointer != 0) {
        delete mNumberGridPointer;
        mNumberGridPointer = 0;
    }
}

NumberGrid& ActionData::getGrid() {
    return *mNumberGridPointer;
}

void ActionData::setGrid( NumberGrid *grid ) {
    if(mNumberGridPointer != 0) {
        delete mNumberGridPointer;
        mNumberGridPointer = 0;
    }
    mNumberGridPointer = grid;
}

ColorTable& ActionData::getTable( ) {
    return mColorTable;
}

