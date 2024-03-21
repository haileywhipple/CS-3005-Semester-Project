#include <iostream>
#include <string>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

#ifndef _ACTION_DATA_H_
#define _ACTION_DATA_H_

// Assignment 4: Continuing Assignments

class ActionData {
    public:
        ActionData(std::istream& is, std::ostream& os);
        std::istream& getIS();
        std::ostream& getOS();
        PPM& getInputImage1();
        PPM& getInputImage2();
        PPM& getOutputImage();
        bool getDone() const;
        void setDone();
        ~ActionData();
        NumberGrid& getGrid();
        void setGrid( NumberGrid *grid );

        ColorTable& getTable( );
        
    protected:
        std::istream& mIS;
        std::ostream& mOS;
        PPM mInputImage1;
        PPM mInputImage2;
        PPM mOutputImage;
        bool mQuit;

        NumberGrid * mNumberGridPointer;
        ColorTable mColorTable;
};

#endif // _ACTION_DATA_H_