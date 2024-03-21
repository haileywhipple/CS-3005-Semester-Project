#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "PPM.h"

PPM::PPM( )
    : Image(0, 0), mMaxColorValue(1) {

}

PPM::PPM( const int& height, const int& width )
    : Image(height, width), mMaxColorValue(1) {
    
}

int PPM::getMaxColorValue( ) const {
    return mMaxColorValue;
}

bool PPM::valueValid( const int& value ) const {
    if( (0 <= value) && (value <= mMaxColorValue) ) {
        return true;
    } else {
        return false;
    }
}

void PPM::setMaxColorValue( const int& max_color_value ) {
    if( ( 1 <= max_color_value) && (max_color_value <= 255) ) {
        mMaxColorValue = max_color_value;
    }
}

void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if( valueValid(value) ) {
        Image::setChannel(row, column, channel, value);
    }
}

void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ) {
    Image::setChannel(row, column, 0, red);
    Image::setChannel(row, column, 1, green);
    Image::setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream& os) const {
    os << "P6 " << mWidth << " " << mHeight << " " << mMaxColorValue << "\n";

    for( int row = 0; row < mHeight; row++ ) {
        for( int column = 0; column < mWidth; column++ ) {
            unsigned char R = Image::getChannel( row, column, 0 );
            unsigned char G = Image::getChannel( row, column, 1 );
            unsigned char B = Image::getChannel( row, column, 2 );
            os.write((char *) &R, 1);
            os.write((char *) &G, 1);
            os.write((char *) &B, 1);
        }
    }
}

void PPM::readStream(std::istream& is) {

    std::string first;
    int width;
    int height;
    int maxColorValue;
    

    is >> first;
    is >> width;
    is >> height;
    is >> maxColorValue;
    is.get(); // skip white space

    Image::setHeight(height);
    Image::setWidth(width);
    setMaxColorValue(maxColorValue);

    unsigned char R;
    unsigned char G;
    unsigned char B;
    

    for( int row = 0; row < height; row++ ) {
        for( int column = 0; column < width; column++ ) {
            is.read((char *) &R, 1);
            is.read((char *) &G, 1);
            is.read((char *) &B, 1);

            Image::setChannel(row, column, 0, R);
            Image::setChannel(row, column, 1, G);
            Image::setChannel(row, column, 2, B);
        }
    }
}

void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    dst.setHeight(height);
    dst.setWidth(width);
    dst.setMaxColorValue(max);

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            int value = this->getChannel(row, column, src_channel);
            dst.setPixel(row, column, value, value, value);
        }
    }
}

void PPM::grayFromRed( PPM& dst ) const {
    grayFromChannel(dst, 0);
}

void PPM::grayFromGreen( PPM& dst ) const {
    grayFromChannel(dst, 1);
}

void PPM::grayFromBlue( PPM& dst ) const {
    grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const {
    int R = getChannel(row, column, 0);
    int G = getChannel(row, column, 1);
    int B = getChannel(row, column, 2);

    double brightness = 0.2126*R + 0.7152*G + 0.0722*B;
    return brightness;
}

void PPM::grayFromLinearColorimetric( PPM& dst ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    dst.setHeight(height);
    dst.setWidth(width);
    dst.setMaxColorValue(max);

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            //int R = this->getChannel(row, column, 0);
            //int G = this->getChannel(row, column, 1);
            //int B = this->getChannel(row, column, 2);

            int value = linearColorimetricPixelValue(row, column);

            dst.setPixel(row, column, value, value, value);
        }
    }
}

// OPERATORS
bool PPM::operator==( const PPM& rhs ) const {
    int pixel_this = this->getHeight()*(this->getWidth());
    int pixel_rhs = rhs.getHeight()*rhs.getWidth();
    if(pixel_this == pixel_rhs) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator!=( const PPM& rhs ) const {
    int pixel_this = this->getHeight()*(this->getWidth());
    int pixel_rhs = rhs.getHeight()*rhs.getWidth();
    if(pixel_this != pixel_rhs) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator<( const PPM& rhs ) const {
    int pixel_this = this->getHeight()*(this->getWidth());
    int pixel_rhs = rhs.getHeight()*rhs.getWidth();
    if(pixel_this < pixel_rhs) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator<=( const PPM& rhs ) const {
    int pixel_this = this->getHeight()*(this->getWidth());
    int pixel_rhs = rhs.getHeight()*rhs.getWidth();
    if(pixel_this <= pixel_rhs) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator>( const PPM& rhs ) const {
    int pixel_this = this->getHeight()*(this->getWidth());
    int pixel_rhs = rhs.getHeight()*rhs.getWidth();
    if(pixel_this > pixel_rhs) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator>=( const PPM& rhs ) const {
    int pixel_this = this->getHeight()*(this->getWidth());
    int pixel_rhs = rhs.getHeight()*rhs.getWidth();
    if(pixel_this >= pixel_rhs) {
        return true;
    } else {
        return false;
    }
}

PPM& PPM::operator+=( const PPM& rhs ) {
    // Assumes *this and rhs have the same width and height. Adds the channel values from rhs into the channels for *this. If the resulting value is larger than max color value, set to max color value. Returns *this.

    for(int column = 0; column < this->getWidth(); column++) {
        for(int row = 0; row < this->getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R + rhs.getChannel(row, column, 0);
            G = G + rhs.getChannel(row, column, 1);
            B = B + rhs.getChannel(row, column, 2);

            int max = this->getMaxColorValue();

            if(R > max) {
                R = max;
            }

            if(G > max) {
                G = max;
            }

            if(B > max) {
                B = max;
            }

            this->setChannel(row, column, 0, R);
            this->setChannel(row, column, 1, G);
            this->setChannel(row, column, 2, B);
        }
    }
    return *this;
}

PPM& PPM::operator-=( const PPM& rhs ) {
    // Assumes *this and rhs have the same width and height. Subtracts the channel values from rhs from the channels for *this. If the resulting value is less than 0, set to 0. Returns *this.
    for(int column = 0; column < this->getWidth(); column++) {
        for(int row = 0; row < this->getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R - rhs.getChannel(row, column, 0);
            G = G - rhs.getChannel(row, column, 1);
            B = B - rhs.getChannel(row, column, 2);
            int min = 0;

            if(R < min) {
                R = min;
            }
            
            if(G < min) {
                G = min;
            }
            
            if(B < min) {
                B = min;
            }

            this->setChannel(row, column, 0, R);
            this->setChannel(row, column, 1, G);
            this->setChannel(row, column, 2, B);
        }
    }
    return *this;
}

PPM& PPM::operator*=( const double& rhs ) {
    for(int column = 0; column < this->getWidth(); column++) {
        for(int row = 0; row < this->getHeight(); row++) {
            int R = rhs*this->getChannel(row, column, 0);
            int G = rhs*this->getChannel(row, column, 1);
            int B = rhs*this->getChannel(row, column, 2);
            int max = this->getMaxColorValue();
            int min = 0;

            if(R > max) {
                R = max;
            }
            
            if(G > max) {
                G = max;
            }
            
            if(B > max) {
                B = max;
            }

            if(R < min) {
                R = min;
            }
            
            if(G < min) {
                G = min;
            }
            
            if(B < min) {
                B = min;
            }

            setChannel(row, column, 0, R);
            setChannel(row, column, 1, G);
            setChannel(row, column, 2, B);
        }
    }
    return *this;
}

PPM& PPM::operator/=( const double& rhs ) {
    for(int column = 0; column < this->getWidth(); column++) {
        for(int row = 0; row < this->getHeight(); row++) {
            int R = this->getChannel(row, column, 0)/rhs;
            int G = this->getChannel(row, column, 1)/rhs;
            int B = this->getChannel(row, column, 2)/rhs;
            int max = this->getMaxColorValue();
            int min = 0;

            if(R > max) {
                R = max;
            }
            
            if(G > max) {
                G = max;
            }
            
            if(B > max) {
                B = max;
            }

            if(R < min) {
                R = min;
            }
            
            if(G < min) {
                G = min;
            }
            
            if(B < min) {
                B = min;
            }

            this->setChannel(row, column, 0, R);
            this->setChannel(row, column, 1, G);
            this->setChannel(row, column, 2, B);
        }
    }
    return *this;
}

PPM PPM::operator+( const PPM& rhs ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    PPM ppm(height, width);
    ppm.setMaxColorValue(max);

    for(int column = 0; column < ppm.getWidth(); column++) {
        for(int row = 0; row < ppm.getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R + rhs.getChannel(row, column, 0);
            G = G + rhs.getChannel(row, column, 1);
            B = B + rhs.getChannel(row, column, 2);
            int max = ppm.getMaxColorValue();

            if(R > max) {
                R = max;
            }
            
            if(G > max) {
                G = max;
            }
            
            if(B > max) {
                B = max;
            }

            ppm.setChannel(row, column, 0, R);
            ppm.setChannel(row, column, 1, G);
            ppm.setChannel(row, column, 2, B);
        }
    }

    return ppm;
}

PPM PPM::operator-( const PPM& rhs ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    PPM ppm(height, width);
    ppm.setMaxColorValue(max);

    for(int column = 0; column < ppm.getWidth(); column++) {
        for(int row = 0; row < ppm.getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R - rhs.getChannel(row, column, 0);
            G = G - rhs.getChannel(row, column, 1);
            B = B - rhs.getChannel(row, column, 2);
            int min = 0;

            if(R < min) {
                R = min;
            }
            
            if(G < min) {
                G = min;
            }
            
            if(B < min) {
                B = min;
            }

            ppm.setChannel(row, column, 0, R);
            ppm.setChannel(row, column, 1, G);
            ppm.setChannel(row, column, 2, B);
        }
    }

    return ppm;
}

PPM PPM::operator*( const double& rhs ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    PPM ppm(height, width);
    ppm.setMaxColorValue(max);

    for(int column = 0; column < ppm.getWidth(); column++) {
        for(int row = 0; row < ppm.getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R * rhs;
            G = G * rhs;
            B = B * rhs;

            int max = ppm.getMaxColorValue();
            int min = 0;

            if(R > max) {
                R = max;
            }
            
            if(G > max) {
                G = max;
            }
            
            if(B > max) {
                B = max;
            }

            if(R < min) {
                R = min;
            }
            
            if(G < min) {
                G = min;
            }
            
            if(B < min) {
                B = min;
            }

            ppm.setChannel(row, column, 0, R);
            ppm.setChannel(row, column, 1, G);
            ppm.setChannel(row, column, 2, B);
        }
    }

    return ppm;
}

PPM PPM::operator/( const double& rhs ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    PPM ppm(height, width);
    ppm.setMaxColorValue(max);
    for(int column = 0; column < ppm.getWidth(); column++) {
        for(int row = 0; row < ppm.getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R / rhs;
            G = G / rhs;
            B = B / rhs;

            int max = ppm.getMaxColorValue();
            int min = 0;

            if(R > max) {
                R = max;
            }
            
            if(G > max) {
                G = max;
            }
            
            if(B > max) {
                B = max;
            }

            if(R < min) {
                R = min;
            }
            
            if(G < min) {
                G = min;
            }
            
            if(B < min) {
                B = min;
            }

            ppm.setChannel(row, column, 0, R);
            ppm.setChannel(row, column, 1, G);
            ppm.setChannel(row, column, 2, B);
        }
    }
    return ppm;
}

// PRACTICE EXAM 10/06/23

void PPM::sepiaFilter( PPM& dst ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    dst.setHeight(height);
    dst.setWidth(width);
    dst.setMaxColorValue(max);

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            int R_o = this->getChannel(row, column, 0);
            int G_o = this->getChannel(row, column, 1);
            int B_o = this->getChannel(row, column, 2);

            int R = 0.393*R_o + 0.769*G_o + 0.189*B_o;
            int G = 0.349*R_o + 0.686*G_o + 0.168*B_o;
            int B = 0.272*R_o + 0.534*G_o + 0.131*B_o;

            if( R > max ) {
                R = max;
            }

            if( G > max ) {
                G = max;
            }

            if( B > max ) {
                B = max;
            }

            dst.setPixel(row, column, R, G, B);
        }
    }
}

PPM& PPM::operator+=( const int& rhs ) {
    for(int column = 0; column < this->getWidth(); column++) {
        for(int row = 0; row < this->getHeight(); row++) {
            int R = this->getChannel(row, column, 0);
            int G = this->getChannel(row, column, 1);
            int B = this->getChannel(row, column, 2);

            R = R + rhs;
            G = G + rhs;
            B = B + rhs;

            int max = this->getMaxColorValue();
            int min = 0;

            if(R > max) {
                R = max;
            }

            if(G > max) {
                G = max;
            }

            if(B > max) {
                B = max;
            }

            if(R < min) {
                R = min;
            }

            if(G < min) {
                G = min;
            }

            if(B < min) {
                B = min;
            }

            this->setChannel(row, column, 0, R);
            this->setChannel(row, column, 1, G);
            this->setChannel(row, column, 2, B);
        }
    }
    return *this;
}

// EXAM 2 10/09/23

void PPM::orangeFilter( PPM& dst ) const {
    int height = this->getHeight();
    int width = this->getWidth();
    int max = this->getMaxColorValue();
    dst.setHeight(height);
    dst.setWidth(width);
    dst.setMaxColorValue(max);

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            int R_o = this->getChannel(row, column, 0);
            int G_o = this->getChannel(row, column, 1);
            int B_o = this->getChannel(row, column, 2);

            int R = 2*(2*R_o+G_o)/3;
            int G = 2*(2*R_o+G_o)/6;
            int B = B_o/2;

            if( R > max ) {
                R = max;
            }

            if( G > max ) {
                G = max;
            }

            if( B > max ) {
                B = max;
            }

            dst.setPixel(row, column, R, G, B);
        }
    }
}

// FINAL EXAM 12/13/23

int PPM::antiAliasPixelValue(int n, int row, int column, int channel) const {

    int big_row = (row)*n;
    int big_column = (column)*n;

    int big_row1 = (row+1)*n;
    int big_column1 = (column+1)*n;
    
    int sum = 0;

    for( int r = big_row; r < big_row1; r++ ) {
        for( int c = big_column; c < big_column1; c++ ) {
            sum += getChannel(r, c, channel);
        }
    }

    sum = sum / (n*n);
    return sum;
}

void PPM::antiAlias(const int& n, PPM& dst) const {
    int height = this->getHeight()/n;
    int width = this->getWidth()/n;
    int max = this->getMaxColorValue();
    dst.setHeight(height);
    dst.setWidth(width);
    dst.setMaxColorValue(max);

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            int R = antiAliasPixelValue(n, row, column, 0);
            int G = antiAliasPixelValue(n, row, column, 1);
            int B = antiAliasPixelValue(n, row, column, 2);

            dst.setPixel(row, column, R, G, B);
        }
    }
}


