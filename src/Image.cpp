#include <iostream>
#include <string>
#include <vector>
#include "Image.h"

Image::Image( )
    : mHeight(0), mWidth(0) {
    mData.resize( mHeight * mWidth * 3 );
}

Image::Image( const int& height, const int& width )
    : mHeight(height), mWidth(width) {
    mData.resize( mHeight * mWidth * 3 );
}

int Image::getHeight() const {
    return mHeight;
}

int Image::getWidth() const {
    return mWidth;
}

bool Image::indexValid( const int& row, const int& column, const int& channel ) const {

    if( (0 <= row) && (0 <= column) && (row < mHeight) && (column < mWidth) && ( 0 <= channel ) && ( channel < 3 ) ) {
        return true;
    } else {
        return false;
    }
}

int Image::index( const int& row, const int& column, const int& channel ) const {
    int index = ((row * mWidth * 3) + (column * 3)) + channel;
    return index;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const {
    int i = index(row, column, channel);
    if (indexValid(row, column, channel) == true) {
        int value = mData[i];
        return value;
    } else {
        return -1;
    }
}

void Image::setHeight( const int& height ) {
    if(height>=0) {
        mHeight = height;
    }
    mData.resize( mHeight * mWidth * 3 );
}

void Image::setWidth( const int& width ) {
    if(width>=0) {
        mWidth = width;
    }
    mData.resize( mHeight * mWidth * 3 );
}

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if (indexValid(row, column, channel) == true) {
        int i = index(row, column, channel);
        mData[ i ] = value;
    }
}