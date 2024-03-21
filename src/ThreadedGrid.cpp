#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <exception>
#include "NumberGrid.h"
#include "ThreadedGrid.h"

ThreadedGrid::ThreadedGrid()
    : NumberGrid() {
    
}

ThreadedGrid::ThreadedGrid(const int& height, const int& width)
    : NumberGrid(height, width) {
    
}

ThreadedGrid::~ThreadedGrid() {
    
}

void ThreadedGrid::calculateAllNumbers() {
    int height = NumberGrid::getHeight();
    std::vector<std::thread> threads;

    // 6 cores
    int thread_count = -1;

    if(thread_count <= 0) {
        thread_count = (int)std::thread::hardware_concurrency();
    }

    mTaskObjects = height; // number of rows
  
    for( int count = 0; count < thread_count; count++ ) {
        threads.push_back( std::thread(&ThreadedGrid::worker, this));
    }

    for( int i = 0; i < thread_count; i++ ) {
        threads[i].join();
    }
}

void ThreadedGrid::worker() {
    int width = getWidth();
    while(true) {
        mAccess.lock();
        if(mTaskObjects < 0) {
            mAccess.unlock();
            break;
        }

        int row = mTaskObjects;
        mTaskObjects = mTaskObjects - 1;
        mAccess.unlock();

        for( int column = 0; column < width; column++) {
            int num = this->calculateNumber(row, column);
            this->setNumber(row, column, num);
        }
    }
}