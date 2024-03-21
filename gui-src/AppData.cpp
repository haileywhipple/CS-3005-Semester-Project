#include "AppData.h"
#include "image_menu.h"
#include <iostream>

AppData::AppData(int height, int width) 
    : mHeight(height), mWidth(width), mActionData(mInputStream, mOutputStream) {
    
    mAntiAliasReductionCount = 2;
    mAntiAlias = false;

    mFractalMode = M_JULIA;

    configureMenu(mMenuData);
    mActionData.setGrid(new ComplexFractal);

    mDebug = 1;
    
    mNumColor = 101;
    mMaxNumber = 200;
    mColor1 = Color(255, 153, 255);
    mColor2 = Color(0, 0, 0);
    mColor3 = Color(255, 255, 255);
    mA = 0.35;
    mB = 0.35;

    mMinX = -2.0;
    mMaxX = 2.0;
    mMinY = -2.0;
    mMaxY = 2.0;

    setColorTable();
    createFractal();
    
}

void AppData::setSize(int height, int width) {
    mHeight = height;
    mWidth = width;
}

int AppData::getHeight() const {
    return mHeight;
}

int AppData::getWidth() const {
    return mWidth;
}

// STARTER CODE ABOVE

PPM& AppData::getOutputImage() {
    return mActionData.getOutputImage();
}

ColorTable& AppData::getColorTable() {
    return mActionData.getTable();
}

void AppData::createJulia1() {
    mFractalMode = M_JULIA;
    selectJulia();
    configureGrid(200);
    juliaParameters(-0.8, 0.156);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();

    mNumColor = 201;
    mColor1 = Color(0, 0, 102);
    mColor2 = Color(255, 255, 102);
    setColorTable();

    gridApplyColorTable();
}

void AppData::createJulia2() {
    mFractalMode = M_JULIA;
    selectJulia();
    configureGrid(200);
    juliaParameters(-0.7269, 0.1889);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();

    mNumColor = 301;
    mColor1 = Color(255, 0, 127);
    mColor2 = Color(255, 255, 255);
    setColorTable();

    gridApplyColorTable();
}

void AppData::createMandelbrot1() {
    mFractalMode = M_MANDELBROT;
    selectMandelbrot();
    configureGrid(200);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();

    mNumColor = 101;
    mColor1 = Color(153, 51, 255);
    mColor2 = Color(204, 229, 255);
    setColorTable();

    gridApplyColorTable();
}

void AppData::createMandelbrot2() {
    mFractalMode = M_MANDELBROT;
    selectMandelbrot();
    configureGrid(200);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();

    mNumColor = 201;
    mColor1 = Color(255, 0, 0);
    mColor2 = Color(255, 204, 153);
    setColorTable();

    gridApplyColorTable();
}

void AppData::createComplexFractal1() {
    mFractalMode = M_COMPLEX;
    selectComplexFractal();
    configureGrid(300);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();

    mNumColor = 201;
    mColor1 = Color(47, 79, 79);
    mColor2 = Color(0, 139, 139);
    setColorTable();

    gridApplyColorTable();
}

void AppData::createComplexFractal2() {
    mFractalMode = M_COMPLEX;
    selectComplexFractal();
    configureGrid(200);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();

    mNumColor = 301;
    mColor1 = Color(224, 255, 255);
    mColor2 = Color(30, 144, 255);
    setColorTable();

    gridApplyColorTable();
}

void AppData::clearStreams() {
    mOutputStream.clear();
    mOutputStream.str("");
    mInputStream.clear();
    mInputStream.str("");
}

void AppData::runCommand(const std::string& choice) {

    if(mDebug) {
        std::cout << choice << "\n";
        std::cout << mInputStream.str();
        takeAction(choice, mMenuData, mActionData);
        std::cout << mOutputStream.str() << "\n";
    } else {
        takeAction(choice, mMenuData, mActionData);
    }

}

void AppData::selectJulia() {
    clearStreams();
    runCommand("julia");
}

void AppData::selectMandelbrot() {
    clearStreams();
    runCommand("mandelbrot");
}

void AppData::selectComplexFractal() {
    clearStreams();
    runCommand("complex-fractal");
}

void AppData::configureGrid(int max) {
    mMaxNumber = max;

    int height = mHeight;
    int width = mWidth;

    if(mAntiAlias) {
        height = height*mAntiAliasReductionCount;
        width = width*mAntiAliasReductionCount;
    }

    clearStreams();
    {
        std::stringstream tmp;
        tmp << height << " " << width << " " << max;
        mInputStream.str(tmp.str());
    }
    runCommand("grid");
}

void AppData::juliaParameters(double a, double b) {

    mA = a;
    mB = b;

    clearStreams();
    {
        std::stringstream tmp;
        tmp << a << " " << b;
        mInputStream.str(tmp.str());
    }
    runCommand("julia-parameters");
}

void AppData::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {

    mMinX = x_min;
    mMaxX = x_max;
    mMinY = y_min;
    mMaxY = y_max;

    clearStreams();
    {
        std::stringstream tmp;
        tmp << x_min << " " << x_max << " " << y_min << " " << y_max;
        mInputStream.str(tmp.str());
    }
    runCommand("fractal-plane-size");
}

void AppData::fractalCalculate() {
    clearStreams();
    runCommand("fractal-calculate");
}

void AppData::gridApplyColorTable() {
    clearStreams();
    runCommand("grid-apply-color-table");
    applyAntiAlias();
}

void AppData::setInteractionMode(InteractionMode mode) {
    mInteractionMode = mode;
}

AppData::InteractionMode AppData::getInteractionMode() const {
    return mInteractionMode;
}

void AppData::setColorTable() {

    clearStreams();
    {
        std::stringstream tmp;
        tmp << mNumColor;
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-table-size");

    std::string r = std::to_string(mColor1.getRed());
    std::string g = std::to_string(mColor1.getGreen());
    std::string b = std::to_string(mColor1.getBlue());

    std::string color1 = r + " " + g + " " + b;

    r = std::to_string(mColor2.getRed());
    g = std::to_string(mColor2.getGreen());
    b = std::to_string(mColor2.getBlue());

    std::string color2 = r + " " + g + " " + b;

    r = std::to_string(mColor3.getRed());
    g = std::to_string(mColor3.getGreen());
    b = std::to_string(mColor3.getBlue());

    std::string color3 = r + " " + g + " " + b;

    clearStreams();
    {
        std::stringstream tmp;

        tmp << "0 " << color1 << " " << int(mNumColor/2) << " " << color2;
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-gradient");

    clearStreams();
    {
        std::stringstream tmp;

        tmp << int(mNumColor/2) << " " << color2 << " " << mNumColor-1 << " " << color3;
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-gradient");

    if(mColorTableMode == CT_RANDOM3) {
        set3RandomColors();
    } else if(mColorTableMode == CT_RANDOM) {
        setAllRandomColors();
    } else if(mColorTableMode == CT_REVERSE) {
        setReverseGradient();
    }

}

void AppData::decreaseColorTableSize() {
    if(mNumColor > 10) {
        mNumColor = mNumColor/1.1;
        setColorTable();
        gridApplyColorTable();
    }
}

void AppData::increaseColorTableSize() {
    if(mNumColor < 1024) {
        mNumColor *= 1.1;
        setColorTable();
        gridApplyColorTable();
    }
}

void AppData::randomColor1() {
    int r = std::rand() % (255+1);
    int g = std::rand() % (255+1);
    int b = std::rand() % (255+1);

    mColor1 = Color(r, g, b);
    setColorTable();
    gridApplyColorTable();
}

void AppData::randomColor2() {
    int r = std::rand() % (255+1);
    int g = std::rand() % (255+1);
    int b = std::rand() % (255+1);

    mColor2 = Color(r, g, b);
    setColorTable();
    gridApplyColorTable();
}

void AppData::randomColor3() {
    int r = std::rand() % (255+1);
    int g = std::rand() % (255+1);
    int b = std::rand() % (255+1);

    mColor3 = Color(r, g, b);
    setColorTable();
    gridApplyColorTable();
}

void AppData::zoomIn() {
    double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
    double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;

    mMinX += dx;
    mMaxX -= dx;
    mMinY += dy;
    mMaxY -= dy;

}

void AppData::zoomOut() {
    double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
    double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;

    if( (mMinX - dx > -2.0) && (mMaxX + dx < 2.0) && (mMinY > -2.0) && (mMaxY < 2.0)) {
        mMinX -= dx;
        mMaxX += dx;
        mMinY -= dy;
        mMaxY += dy;
    }
}

void AppData::moveLeft() {
    double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
    
    if(mMinX - dx >= -2.0) {
        mMinX -= dx;
        mMaxX -= dx;
    }
}

void AppData::moveRight() {
    double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
    
    if(mMinX - dx >= -2.0) {
        mMinX += dx;
        mMaxX += dx;
    }
}

void AppData::moveDown() {
    double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
    
    if(mMinY - dy >= -2.0) {
        mMinY -= dy;
        mMaxY -= dy;
    }
}

void AppData::moveUp() {
    double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
    
    if(mMinY - dy >= -2.0) {
        mMinY += dy;
        mMaxY += dy;
    }
}

void AppData::setFractalMode(FractalMode mode) {
    mFractalMode = mode;
}

AppData::FractalMode AppData::getFractalMode() const {
    return mFractalMode;
}

void AppData::increaseMaxNumber() {
    if( mMaxNumber < 2048) {
        mMaxNumber *= 1.1;
    }
}

void AppData::decreaseMaxNumber() {
    if( mMaxNumber > 11) {
        mMaxNumber /= 1.1;
    }
}

void AppData::setAB(int x, int y) {
    if( (mFractalMode == M_MANDELBROT) ) {
        ComplexFractal* object_ = dynamic_cast<ComplexFractal*>(&mActionData.getGrid());
        
        if(object_ != 0) {
            mA = mMinX + x * object_->getDeltaX();
            mB = mMinY + y * object_->getDeltaY();
        }
    }
}

void AppData::resetPlane() {
    mMinX = -2.0;
    mMaxX = 2.0;
    mMinY = -2.0;
    mMaxY = 2.0;
}

void AppData::createFractal() {

    if(mFractalMode == M_MANDELBROT) {
        selectMandelbrot();
        configureGrid(mMaxNumber);
        fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
        fractalCalculate();
        gridApplyColorTable();
    }

    if(mFractalMode == M_JULIA) {
        selectJulia();
        configureGrid(mMaxNumber);
        juliaParameters(mA, mB);
        fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
        fractalCalculate();
        gridApplyColorTable();
    }

    if(mFractalMode == M_COMPLEX) {
        selectComplexFractal();
        configureGrid(mMaxNumber);
        fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
        fractalCalculate();
        gridApplyColorTable();
    }
}

// Practice Exam  4: 12/06/2023

void AppData::nextColorTableMode() {
    if(mColorTableMode == CT_GRADIENT) {
        mColorTableMode = CT_RANDOM3;
    } else if(mColorTableMode == CT_RANDOM3) {
        mColorTableMode = CT_RANDOM;
    } else if(mColorTableMode == CT_RANDOM) {
        mColorTableMode = CT_REVERSE;
    } else if(mColorTableMode == CT_REVERSE) {
        mColorTableMode = CT_GRADIENT;
    }

    setColorTable();
    gridApplyColorTable();
}

AppData::ColorTableMode AppData::getColorTableMode() const {
    return mColorTableMode;
}

void AppData::set3RandomColors() {

    clearStreams();
    {
        std::stringstream tmp;
        tmp << "0";
        mInputStream.str(tmp.str());
    }
    runCommand("set-random-color");

    clearStreams();
    {
        std::stringstream tmp;
        tmp << int(mNumColor/2);
        mInputStream.str(tmp.str());
    }
    runCommand("set-random-color");

    clearStreams();
    {
        std::stringstream tmp;
        tmp << mNumColor-1;
        mInputStream.str(tmp.str());
    }
    runCommand("set-random-color");
}

void AppData::setAllRandomColors() {
    for(int p = 0; p < mNumColor; p++) {
        // for each position in the color table
        clearStreams();
        {
            std::stringstream tmp;
            tmp << p;
            mInputStream.str(tmp.str());
        }
        runCommand("set-random-color");
    }
}

void AppData::setReverseGradient() {

    clearStreams();
    {
        std::stringstream tmp;

        std::string r = std::to_string(mColor1.getRed());
        std::string g = std::to_string(mColor1.getGreen());
        std::string b = std::to_string(mColor1.getBlue());

        std::string color1 = r + " " + g + " " + b;

        r = std::to_string(mColor2.getRed());
        g = std::to_string(mColor2.getGreen());
        b = std::to_string(mColor2.getBlue());

        std::string color2 = r + " " + g + " " + b;

        tmp << "0 " << color1 << " " << int(mNumColor/2) << " " << color2;
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-gradient");


    clearStreams();
    {
        std::stringstream tmp;

        std::string r = std::to_string(mColor1.getRed());
        std::string g = std::to_string(mColor1.getGreen());
        std::string b = std::to_string(mColor1.getBlue());

        std::string color1 = r + " " + g + " " + b;

        r = std::to_string(mColor2.getRed());
        g = std::to_string(mColor2.getGreen());
        b = std::to_string(mColor2.getBlue());

        std::string color2 = r + " " + g + " " + b;

        tmp << int(mNumColor/2) << " " << color2 << " " << mNumColor-1 << " " << color1;
        mInputStream.str(tmp.str());
    }
    runCommand("set-color-gradient");
}


// Exam  4: 12/08/2023

void AppData::increaseChannel(Color& color, int channel) {

    if(color.getChannel(channel)+10 > 255) {
        color.setChannel(channel, 255);
    } else {
        color.setChannel(channel, color.getChannel(channel)+10);
    }

    setColorTable();
    gridApplyColorTable();

}

void AppData::decreaseChannel(Color& color, int channel) {
    
    if(color.getChannel(channel)-10 < 0) {
        color.setChannel(channel, 0);
    } else {
        color.setChannel(channel, color.getChannel(channel)-10);
    }
    
    setColorTable();
    gridApplyColorTable();

}

Color& AppData::fetchColor() {
    if(getInteractionMode() == IM_COLOR1) {
        return mColor1;
    } else if(getInteractionMode() == IM_COLOR2) {
        return mColor2;
    } else if(getInteractionMode() == IM_COLOR3) {
        return mColor3;
    } else {
        static Color color;
        return color;
    }
}

void AppData::increaseRed() {
    increaseChannel(fetchColor(), 0);
}

void AppData::decreaseRed() {
    decreaseChannel(fetchColor(), 0);
}

void AppData::increaseGreen() {
    increaseChannel(fetchColor(), 1);
}

void AppData::decreaseGreen() {
    decreaseChannel(fetchColor(), 1);
}

void AppData::increaseBlue() {
    increaseChannel(fetchColor(), 2);
}

void AppData::decreaseBlue() {
    decreaseChannel(fetchColor(), 2);
}

// Final Exam: 12/13/23

void AppData::copyOutputToInput1() {
    runCommand("copyo1");
}

void AppData::antiAlias(int reduction_count) {
    clearStreams();
    {
        std::stringstream tmp;
        tmp << reduction_count;
        mInputStream.str(tmp.str());
    }
    runCommand("anti-alias");
}

void AppData::applyAntiAlias() {
    if(mAntiAlias) {
        copyOutputToInput1();
        antiAlias(mAntiAliasReductionCount);
    }
}

void AppData::toggleAntiAlias() {
    
    if(mAntiAlias) {
        mAntiAlias = false;
    } else {
        mAntiAlias = true;
    }
}

void AppData::increaseAntiAliasReductionCount() {
    mAntiAliasReductionCount += 1;
}

void AppData::decreaseAntiAliasReductionCount() {
    mAntiAliasReductionCount -= 1;

    if(mAntiAliasReductionCount < 2) {
        mAntiAliasReductionCount = 2;
    }
}
