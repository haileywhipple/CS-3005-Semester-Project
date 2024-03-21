#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"
#include <sstream>

GlutApp::GlutApp(int height, int width)
    : mData(height, width) {
}

void GlutApp::setSize(int height, int width) {
    mData.setSize(height, width);
    mData.createFractal();
}

int GlutApp::getHeight() const {
    return mData.getHeight();
}

int GlutApp::getWidth() const {
    return mData.getWidth();
}

void GlutApp::display() {
    glBegin( GL_POINTS );
    if(mData.getInteractionMode() == mData.IM_FRACTAL) {
        displayOutputImage();
    }

    if(mData.getInteractionMode() == mData.IM_COLORTABLE) {
        displayColorTable();
    } else if(mData.getInteractionMode() == mData.IM_COLOR1) {
        displayColorTable();
    } else if(mData.getInteractionMode() == mData.IM_COLOR2) {
        displayColorTable();
    } else if(mData.getInteractionMode() == mData.IM_COLOR3) {
        displayColorTable();
    }

    glEnd();
}

void GlutApp::displayOutputImage() {
    PPM& p = mData.getOutputImage();
    double max = static_cast<double>(p.getMaxColorValue());
    double r, g, b;
    int row, column;
    for(row = 0; row < p.getHeight(); row++) {
        for(column = 0; column < p.getWidth(); column++) {
            r = p.getChannel(row, column, 0) / max;
            g = p.getChannel(row, column, 1) / max;
            b = p.getChannel(row, column, 2) / max;
            glColor3d(r, g, b);
            glVertex2i(column, p.getHeight()-row-1);
        }
    }
}

void GlutApp::displayColorTable() {
    ColorTable& table = mData.getColorTable();

    for(int row = 0; row < getHeight(); row++) {
        for(int column = 0; column < getWidth(); column++) {
            int i = column * table.getNumberOfColors() / mData.getWidth();

            double r = table[i].getRed() / 255.0;
            double g = table[i].getGreen() / 255.0;
            double b = table[i].getBlue() / 255.0;

            glColor3d(r, g, b);
            glVertex2i(column, row);
        }
    }
}

bool GlutApp::keyboard(unsigned char c) {
    bool post_redisplay = true;
    switch(c) {
    case 'J':
        mData.createJulia1();
        break;
    case 'j':
        mData.createJulia2();
        break;
    case 'M':
        mData.createMandelbrot1();
        break;
    case 'm':
        mData.createMandelbrot2();
        break;
    case 'C':
        mData.createComplexFractal1();
        break;
    case 'c':
        mData.createComplexFractal2();
        break;
    case 'T':
        mData.setInteractionMode(mData.IM_COLORTABLE);
        break;
    case 't':
        mData.setInteractionMode(mData.IM_FRACTAL);
        break;
    case 'b':
        mData.setFractalMode(mData.M_MANDELBROT);
        mData.createFractal();
        break;
    case 'n':
        mData.setFractalMode(mData.M_JULIA);
        mData.createFractal();
        break;
    case 'F':
        mData.setFractalMode(mData.M_COMPLEX);
        mData.createFractal();
        break;
    case '>':
        mData.increaseColorTableSize();
        break;
    case '.':
        mData.increaseColorTableSize();
        break;
    case '<':
        mData.decreaseColorTableSize();
        break;
    case ',':
        mData.decreaseColorTableSize();
        break;
    case 'r':
        if( mData.getInteractionMode() == mData.IM_COLORTABLE ) {
            mData.randomColor1();
        }
        break;
    case 'R':
        if( mData.getInteractionMode() == mData.IM_COLORTABLE ) {
            mData.randomColor2();
        } else if( mData.getInteractionMode() == mData.IM_FRACTAL ) {
            mData.resetPlane();
            mData.createFractal();
        }
        break;
    case 'z':
        mData.zoomIn();
        mData.createFractal();
        break;
    case 'Z':
        mData.zoomOut();
        mData.createFractal();
        break;
    case '+':
        mData.increaseMaxNumber();
        mData.createFractal();
        break;
    case '=':
        mData.increaseMaxNumber();
        mData.createFractal();
        break;
    case '-':
        mData.decreaseMaxNumber();
        mData.createFractal();
        break;
    case '_':
        mData.decreaseMaxNumber();
        mData.createFractal();
        break;
    case '0':
        mData.nextColorTableMode();
        break;
    case '1':
        mData.setInteractionMode(mData.IM_COLOR1);
        break;
    case '2':
        mData.setInteractionMode(mData.IM_COLOR2);
        break;
    case '3':
        mData.setInteractionMode(mData.IM_COLOR3);
        break;
    case 'Y':
        mData.increaseRed();
        break;
    case 'y':
        mData.decreaseRed();
        break;
    case 'U':
        mData.increaseGreen();
        break;
    case 'u':
        mData.decreaseGreen();
        break;
    case 'I':
        mData.increaseBlue();
        break;
    case 'i':
        mData.decreaseBlue();
        break;
    case 'e':
        mData.randomColor3();
        break;
    case 'a':
        mData.toggleAntiAlias();
        mData.createFractal();
        break;
    case 's':
        mData.decreaseAntiAliasReductionCount();
        mData.createFractal();
        break;
    case 'S':
        mData.increaseAntiAliasReductionCount();
        mData.createFractal();
        break;
    default:
        post_redisplay = false;
        break;
    }
    return post_redisplay;
}

bool GlutApp::special(unsigned char c) {
    bool post_redisplay = true;
    switch(c) {
    case GLUT_KEY_LEFT:
        mData.moveLeft();
        mData.createFractal();
        break;
    case GLUT_KEY_RIGHT:
        mData.moveRight();
        mData.createFractal();
        break;
    case GLUT_KEY_DOWN:
        mData.moveDown();
        mData.createFractal();
        break;
    case GLUT_KEY_UP:
        mData.moveUp();
        mData.createFractal();
        break;
    default:
        post_redisplay = false;
        break;
    }
    return post_redisplay;
    
}

bool GlutApp::mouse(int mouse_button, int state, int x, int y) {
    bool post_redisplay = false;
    int xdisplay = x;
    int ydisplay = g_app_data->getHeight() - y;

    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if( mData.getFractalMode() != mData.M_JULIA ) {
            post_redisplay = true;
            mData.setAB(xdisplay, ydisplay);
            mData.setFractalMode(mData.M_JULIA);
            mData.createFractal();
        }
    }
    return post_redisplay;
}

