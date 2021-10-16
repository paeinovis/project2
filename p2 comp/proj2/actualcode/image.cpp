#include "image.h"
#include <vector>
#include "string"
#include <iomanip>
#include <algorithm>
using namespace std;



// Constructors

Image::Image() {
    imageName = "";
}

Image::Image(string imagename) {
    imageName = imagename;
}

// Image / Data Storage

bool Image::LoadAndSave() { // Loads data from given Image, returns false if data can't be opened
    // or closed. Is successful if it opens, stores, and closes file.
    bool open = this->LoadFile();
    bool success = false;

    if (open) {
        try {
            this->StoreData();
        } catch (const exception& e) {
            success = false;
            return success;
        }
    } else {
        return success;
    }

    bool closed = this->CloseFile();
    if (closed) {
        success = true;
    }
    return success;
}

void Image::SaveNewImage(string filename) {
    ofstream file(filename);

    imageName = filename;

    file.write((char *)&idLength, 1);
    file.write((char *)&colorMapType, 1);
    file.write((char *)&dataTypeCode, 1);
    file.write((char *)&colorMapOrigin, 2);
    file.write((char *)&colorMapLength, 2);
    file.write((char *)&colorMapDepth, 1);
    file.write((char *)&xOrigin, 2);
    file.write((char *)&yOrigin, 2);
    file.write((char *)&width, 2);
    file.write((char *)&height, 2);
    file.write((char *)&bitsPerPixel, 1);
    file.write((char *)&imageDescriptor, 1);

    for (int x = 0; x < (int) RGB_ImageData[x].size(); x++) {
        vector<unsigned  char> currentRX = redVector->at(x);
        vector<unsigned  char> currentGX = greenVector->at(x);
        vector<unsigned  char> currentBX = blueVector->at(x);

        for (unsigned int y = 0; y < RGB_ImageData->size(); y++) {
            file.write((char *)&currentBX.at(y), 1);
            file.write((char *)&currentGX.at(y), 1);
            file.write((char *)&currentRX.at(y), 1);
        }
    }
}

void Image::SaveVectAsImage(string filename, compVect* vectToSave, \
unsigned int xPixel, unsigned int yPixel) {
    width = xPixel;
    height = yPixel;
//    pixels = width * height;
    imageName = filename;
}



// Image Manipulation / Behavior

void Image::Multiply(Image *top, Image *bottom) {
//    int normalTopMaxR = top->RmaxValue;
//    int normalTopMaxG = top->GmaxValue;
//    int normalTopMaxB = top->BmaxValue;
//
//    int normalBotMaxR = bottom->RmaxValue;
//    int normalBotMaxG = bottom->GmaxValue;
//    int normalBotMaxB = bottom->BmaxValue;

    // Takes header of top

    idLength = top->idLength;
    colorMapType = top->colorMapType;
    dataTypeCode = top->dataTypeCode;
    colorMapOrigin = top->colorMapOrigin;
    colorMapLength = top->colorMapLength;
    colorMapDepth = top->colorMapDepth;
    xOrigin = top->xOrigin;
    yOrigin = top->yOrigin;
    width = top->width;
    height = top->height;
    bitsPerPixel = top->bitsPerPixel;
    imageDescriptor = top->imageDescriptor;

    double multRTemp;
    double multGTemp;
    double multBTemp;

    unsigned char red, green, blue;

    compVect RGB_ImageData_temp;
    rgb red_rgb_temp;
    rgb green_rgb_temp;
    rgb blue_rgb_temp;

    for (int x = 0; x < (int) width; x++) {
        vector<unsigned char> redTemp;
        vector<unsigned char> greenTemp;
        vector<unsigned char> blueTemp;

        vector<rgbCoords> rgbTemp;

        vector<rgbCoords> currentX_T = top->RGB_ImageData->at(x);

        vector<rgbCoords> currentX_B = bottom->RGB_ImageData->at(x);

        for (int y = 0; y < (int) height; y++) {

            multRTemp = (((int) currentX_T.at(y).r) / (255.0)) * (((int) currentX_B.at(y).r) / (255.0));
            multGTemp = (((int) currentX_T.at(y).g) / (255.0)) * (((int) currentX_B.at(y).g) / (255.0));
            multBTemp = (((int) currentX_T.at(y).b) / (255.0)) * (((int) currentX_B.at(y).b) / (255.0));

            red = (int) (multRTemp + .5f);
            green = (int) (multGTemp + .5f);
            blue = (int) (multBTemp + .5f);

            redTemp.push_back(red);
            greenTemp.push_back(green);
            blueTemp.push_back(blue);

            struct rgbCoords rgbVect = {red, green, blue};
            rgbTemp.push_back(rgbVect);
        }

        RGB_ImageData_temp.push_back(rgbTemp);

        red_rgb_temp.push_back(redTemp);
        green_rgb_temp.push_back(greenTemp);
        blue_rgb_temp.push_back(blueTemp);
    }

    RGB_ImageData = &RGB_ImageData_temp;

    redVector = &red_rgb_temp;
    greenVector = &green_rgb_temp;
    blueVector = &blue_rgb_temp;

}


void Image::Subtract(Image *top, Image *bottom) {
}

void Image::Combine() {
}

void Image::RotateOneEighty() {

}

// Getters

rgb *Image::GetRed() {
    return redVector;
}

rgb *Image::GetGreen() {
    return greenVector;
}

rgb *Image::GetBlue() {
    return blueVector;
}


// Private

void Image::StoreData() {
    unsigned char red, green, blue;
//    int RMaxTemp = 0;
//    int GMaxTemp = 0;
//    int BMaxTemp = 0;

//    int RMinTemp = 0;
//    int GMinTemp = 0;
//    int BMinTemp = 0;

    ifstream file(imageName, ios_base::binary);

    file.read((char *)&idLength, 1);
    file.read((char *)&colorMapType, 1);
    file.read((char *)&dataTypeCode, 1);
    file.read((char *)&colorMapOrigin, 2);
    file.read((char *)&colorMapLength, 2);
    file.read((char *)&colorMapDepth, 1);
    file.read((char *)&xOrigin, 2);
    file.read((char *)&yOrigin, 2);
    file.read((char *)&width, 2);
    file.read((char *)&height, 2);
    file.read((char *)&bitsPerPixel, 1);
    file.read((char *)&imageDescriptor, 1);

    pixels = width * height;

    compVect RGB_ImageData_temp;

    rgb red_rgb_temp;
    rgb green_rgb_temp;
    rgb blue_rgb_temp;

    redVector->resize(pixels);
    greenVector->resize(pixels);
    blueVector->resize(pixels);

    redVector->reserve(pixels);
    greenVector->reserve(pixels);
    blueVector->reserve(pixels);

    RGB_ImageData->reserve(pixels);

    for (int x = 0; x < (int) width; x++) {
        vector<unsigned char> redTemp;
        vector<unsigned char> greenTemp;
        vector<unsigned char> blueTemp;

        vector<rgbCoords> rgbTemp;

        for (int y = 0; y < (int) height; y++) {
            file.read((char *)&blue, 1);
            file.read((char *)&green, 1);
            file.read((char *)&red, 1);

            redTemp.push_back(red);
            greenTemp.push_back(green);
            blueTemp.push_back(blue);

//            if (RMaxTemp < (int) red) {
//                RMaxTemp = (int) red;
//            }
//            if (GMaxTemp < (int) green) {
//                GMaxTemp = (int) green;
//            }
//            if (BMaxTemp < (int) blue) {
//                BMaxTemp = (int) blue;
//            }
//            if (RMinTemp > (int) red) {
//                RMinTemp = (int) red;
//            }
//            if (GMinTemp > (int) green) {
//                GMinTemp = (int) green;
//            }
//            if (BMinTemp > (int) blue) {
//                BMinTemp = (int) blue;
//            }
            struct rgbCoords rgbVect = {red, green, blue};
            rgbTemp.push_back(rgbVect);
        }

        RGB_ImageData_temp.push_back(rgbTemp);

        red_rgb_temp.push_back(redTemp);
        green_rgb_temp.push_back(greenTemp);
        blue_rgb_temp.push_back(blueTemp);
    }

    RGB_ImageData = &RGB_ImageData_temp;

    redVector = &red_rgb_temp;
    greenVector = &green_rgb_temp;
    blueVector = &blue_rgb_temp;

//    RmaxValue = RMaxTemp;
//    GmaxValue = GMaxTemp;
//    BmaxValue = BMaxTemp;

//    RminValue = RMinTemp;
//    GminValue = GMinTemp;
//    BminValue = BMinTemp;

}

bool Image::LoadFile() {
    inFS.open(imageName, ios_base::binary);
    bool opened = false;
    if (inFS.is_open()) {
        cout << "File " + imageName + " opened successfully.\n";
        opened = true;
    }
    else {
        cout << "File " + imageName + " failed to open.\n";
    }
    return opened;
}

bool Image::CloseFile() {
    inFS.close();
    bool closed = false;
    if (!inFS.is_open()) {
        cout << "File " + imageName + " closed successfully.\n";
        closed = true;
    }
    else {
        cout << "File " + imageName + " failed to close.\n";
    }
    return closed;
}

//compVect* Image::RGBtoBGR(compVect* vectToChange,  unsigned int yPixel, unsigned int xPixel) {
//    compVect *toReturn;
//    unsigned char blue, green, red;
//
//    for (unsigned int y = 0; y < vectToChange[y].size(); y++) {
//        vector<rgbCoords> temp;
//        for (unsigned int x = 0; x < vectToChange->size(); x++) {
//            blue = vectToChange[x][y].b;
//            green = vectToChange[x][y].g;
//            red = vectToChange[x][y].r;
//
//            struct rgbCoords vect = {red, green, blue};
//
//            temp.push_back(vect);
//        }
//        toReturn.push_back(temp);
//    }
//    return toReturn;
//}
//
//compVect* Image::BGRtoRGB(compVect* vectToChange, unsigned int yPixel, unsigned int xPixel) {
//    compVect* toReturn;
//    unsigned char red, green, blue;
//
//    for (unsigned int y = 0; y < vectToChange[y].size(); y++) {
//        vector<rgbCoords> temp;
//        for (unsigned int x = 0; x < vectToChange->size(); x++) {
//            red = vectToChange[x][y].r;
//            green = vectToChange[x][y].g;
//            blue = vectToChange[x][y].b;
//
//            struct rgbCoords vect = {red, green, blue};
//
//            temp.push_back(vect);
//        }
//        toReturn.push_back(temp);
//    }
//    return toReturn;
//}



