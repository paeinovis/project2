#include <iomanip>
#include <iostream>
#include <fstream>
#include "image.h"
using namespace std;
int main() {

    string car = "./input/car.tga";
    string circle = "./input/circles.tga";
    string redLayer = "./input/layer_red.tga";
    string greenLayer = "./input/layer_green.tga";
    string blueLayer = "./input/layer_blue.tga";
    string layer1 = "./input/layer1.tga";
    string pattern1 = "./input/pattern1.tga";
    string pattern2 = "./input/pattern2.tga";
    string text = "./input/text.tga";
    string text2 = "./input/text.tga";

    Image blankImage = Image();

    cout << "Which test to run?\n";
    cout << "Enter Number 1-10:   ";
    int option;
    cin >> option;

    switch (option) {
        case 1: {
            Image lay1Image = Image(layer1);
            lay1Image.LoadAndSave();
            Image patternImage = Image(pattern1);
            patternImage.LoadAndSave();
            blankImage.Multiply(&lay1Image, &patternImage);
            blankImage.SaveNewImage("part1.tga");
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
        case 5: {
            break;
        }
        case 6: {
            break;
        }
        case 7: {
            break;
        }
        case 9: {
            break;
        }
        case 10: {
            break;
        }
        default: {
            cout << "Something went wrong.\n";
        }
    }







































    return 0;
}
