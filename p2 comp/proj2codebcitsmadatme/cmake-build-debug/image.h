#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#ifndef PROJ2CODEBCITSMADATME_IMAGE_H
#define PROJ2CODEBCITSMADATME_IMAGE_H
using namespace std;

typedef vector<vector<array<unsigned char, 3>>> compVect;
// short for complicatedVector but that isn't a pretty variable name.
typedef vector<vector<unsigned char>> rgb;

class Image {
    // Header Vars              // Bytes
    string imageName;
    char idLength;              // 1b
    char colorMapType;          // 1b
    char dataTypeCode;          // 1b
    short colorMapOrigin;       // 2b
    short colorMapLength;       // 2b
    char colorMapDepth;         // 1b
    unsigned int xOrigin;       // 2b
    unsigned int yOrigin;       // 2b
    unsigned int width;         // 2b
    unsigned int height;        // 2b
    char bitsPerPixel;          // 1b
    char imageDescriptor;       // 1b

    // Image Data (Variable Length)
    unsigned int pixels;

    rgb* RedVector;
    rgb* GreenVector;
    rgb* BlueVector;

    compVect* BGR_ImageData;
    compVect* RGB_ImageData;
    // Yes this is funky but it makes sense to me (I think)
    // But in case it doesn't in the future:
    // Vector Y of vector X of BGR or RGB, of arrays of 3 w the datatype unsigned int
    // So BGR/RGB_ImageData[Y][X][RGB]
    // Should go across rows, starting at Y = 0 (as to match the way the data is stored)

    ifstream inFS;

public:
    // Constructors
    Image();
    Image(string imagename);

    // Image / Data Storage
    bool LoadAndSave();
    void SaveNewImage(Image* ImageToSave);
    void SaveVectAsImage(string filename, compVect *vectToSave, \
        unsigned int xPixel, unsigned int yPixel, bool toRGB = true);

    // Image Manipulation / Behavior
    Image* Multiply(Image* top, Image* bottom);
    Image* Subtract(Image* top, Image* bottom);
    Image* Combine(compVect* R, compVect* G, compVect* B);
    Image* Screen();
    Image* Overlay();
    void RotateOneEighty();

    // Getters
    rgb* GetRed();
    rgb* GetGreen();
    rgb* GetBlue();

private:
    void StoreData();
    bool LoadFile();
    bool CloseFile();
    compVect* RGBtoBGR(compVect* compToChange, unsigned int yPixel, unsigned int xPixel);
    compVect* BGRtoRGB(compVect* compToChange, unsigned int yPixel, unsigned int xPixel);
};


#endif //PROJ2CODEBCITSMADATME_IMAGE_H
