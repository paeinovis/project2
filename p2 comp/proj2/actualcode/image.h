#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#ifndef ACTUALCODE_IMAGE_H
#define ACTUALCODE_IMAGE_H
using namespace std;

struct rgbCoords {
    unsigned char r, g, b;
};

typedef vector<vector<rgbCoords>> compVect;
typedef vector<vector<unsigned char>> rgb;

class Image {
    // Header Vars                  // Bytes
    string imageName;
    char idLength;                  // 1b
    char colorMapType = 0;          // 1b
    char dataTypeCode = 0;          // 1b
    short colorMapOrigin = 0;       // 2b
    short colorMapLength = 0;       // 2b
    char colorMapDepth = 0;         // 1b
    int xOrigin = 0;                // 2b
    int yOrigin = 0;                // 2b
    int width = 0;                  // 2b
    int height = 0;                 // 2b
    char bitsPerPixel = 0;          // 1b
    char imageDescriptor = 0;       // 1b

    // Image Data (Variable Length)
    unsigned int pixels;

//    int RmaxValue = 0;
//    int GmaxValue = 0;
//    int BmaxValue = 0;

//    int RminValue;
//    int BminValue;
//    int GminValue;

    rgb* redVector = nullptr;
    rgb* greenVector = nullptr;
    rgb* blueVector = nullptr;

    compVect* RGB_ImageData = nullptr;

    ifstream inFS;

public:
    // Constructors
    Image();
    Image(string imagename);

    // Image / Data Storage
    bool LoadAndSave();
    void SaveNewImage(string filename);
    void SaveVectAsImage(string filename, compVect *vectToSave, \
        unsigned int xPixel, unsigned int yPixel);

    // Image Manipulation / Behavior
    void Multiply(Image* top, Image* bottom);
    void Subtract(Image* top, Image* bottom);
    void Combine();
    void Screen();
    void Overlay();
    void RotateOneEighty();

    // Getters
    rgb* GetRed();
    rgb* GetGreen();
    rgb* GetBlue();


private:
    void StoreData();
    bool LoadFile();
    bool CloseFile();
//    compVect* RGBtoBGR(compVect* compToChange, unsigned int yPixel, unsigned int xPixel);
//    compVect* BGRtoRGB(compVect* compToChange, unsigned int yPixel, unsigned int xPixel);
    };


#endif //ACTUALCODE_IMAGE_H
