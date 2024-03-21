#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include "NumberGrid.h"

#ifndef _THREADED_GRID_H_
#define _THREADED_GRID_H_

class ThreadedGrid: public NumberGrid {
    public:
        ThreadedGrid();
        ThreadedGrid(const int& height, const int& width);
        virtual ~ThreadedGrid();
        virtual void calculateAllNumbers();
        virtual void worker();
        
    protected:
        int mTaskObjects;
        std::mutex mAccess;
};

#endif // _THREADED_GRID_H_