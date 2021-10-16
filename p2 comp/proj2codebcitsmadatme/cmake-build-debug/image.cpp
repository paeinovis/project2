#include "image.h"
#include <vector>
#include "string"
#include <iomanip>
using namespace std;

int oneByte=1;          // 8 bits
int twoByte=2;          // 16 bits


// Constructors

Image::Image() {
    imageName = "";
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
}

Image::Image(string imagename) {
    imageName = imagename;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
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

void Image::SaveNewImage(Image *imageToSave) {

}

void Image::SaveVectAsImage(string filename, compVect *vectToSave, \
unsigned int xPixel, unsigned int yPixel, bool toRGB = true) {      // true for RGB values, false for BGR
    width = xPixel;
    height = yPixel;

    Image newImage = Image(filename);

    if (toRGB){
        newImage.RGB_ImageData = vectToSave;
        newImage.BGR_ImageData = RGBtoBGR(vectToSave, yPixel, xPixel);
    }
    else {
        newImage.BGR_ImageData = vectToSave;
        newImage.RGB_ImageData = BGRtoRGB(vectToSave, yPixel, xPixel);
    }
}



// Image Manipulation / Behavior

Image* Image::Multiply(Image *top, Image *bottom) {
    return nullptr;
}

Image* Image::Subtract(Image *top, Image *bottom) {
    return nullptr;
}


Image* Image::Combine(compVect *R, compVect *G, compVect *B) {
    return nullptr;
}

void Image::RotateOneEighty() {

}


// Getters

rgb *Image::GetRed() {
    return RedVector;
}

rgb *Image::GetGreen() {
    return GreenVector;
}

rgb *Image::GetBlue() {
    return BlueVector;
}


// Private

void Image::StoreData() {
    unsigned char bgrArray[3];
    unsigned char rgbArray[3];
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    ifstream file(imageName, ios_base::binary);

    char* bleh; // Just hardcoding these vars to be 0 and using bleh to read over the bytes (2, 2, 1, 2, 2 = 9)
    // (Otherwise would have written the same lines with the respective var)

    file.read((char *)&idLength, 1);
    file.read((char *)&colorMapType, 1);
    file.read((char *)&dataTypeCode, 1);
    file.read((bleh, 9);
    file.read((char *)&width, 2);
    file.read((char *)&height, 2);
    file.read((char *)&bitsPerPixel, 1);
    file.read((char *)&imageDescriptor, 1);

    pixels = width * height;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < height; x++) {
            file.read((char *)&blue, 8);
            file.read((char *)&green, 8);
            file.read((char *)&red, 8);

            // BGR
            bgrArray = {blue, green, red};

            // RGB
            rgbArray = {red, green, blue};

            RedVector[x][y] = red;
            GreenVector[x][y] = green;
            BlueVector[x][y] = blue;

        }
    }
























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

compVect* Image::RGBtoBGR(compVect* vectToChange,  unsigned int yPixel, unsigned int xPixel) {
    compVect *toReturn;
    unsigned char bgrArray[3];
    for (unsigned int y = 0; y < yPixel; y++) {
        for (unsigned int x = 0; x < xPixel; x++) {
            bgrArray[0] = vectToChange[x][y][2]; // Blue
            bgrArray[1] = vectToChange[x][y][1]; // Green
            bgrArray[2] = vectToChange[x][y][0]; // Red
            toReturn->push_back(BGR);
        }
    }
    return toReturn;
}

compVect* Image::BGRtoRGB(compVect* vectToChange, unsigned int yPixel, unsigned int xPixel) {
    compVect* toReturn;
    unsigned char rgbArray[3];
    for (unsigned int y = 0; y < yPixel; y++) {
        for (unsigned int x = 0; x < xPixel; x++){
            rgbArray[0] = vectToChange[x][y][2]; // Red
            rgbArray[1] = vectToChange[x][y][1]; // Green
            rgbArray[2] = vectToChange[x][y][0]; // Blue
            toReturn[x][y]->push_back(BGR);
        }
    }
    return toReturn;
}

