#include <iomanip>
#include <iostream>
#include <fstream>
#include "image.h"
using namespace std;
int main() {

    string car = "car.tga";
    string circle = "circles.tga";
    string redLayer = "layer_red.tga";
    string greenLayer = "layer_green.tga";
    string blueLayer = "layer_blue.tga";
    string layer1 = "layer1.tga";
    string pattern1 = "pattern1.tga";
    string pattern2 = "pattern2.tga";
    string text = "text.tga";
    string text2 = "text.tga";

    cout << "Which test to run?\n";
    cout << "Enter Number 1-10: ";
    int option;
    cin >> option;

    switch (option) {
        case 1: {
            Image carImage = Image(car);
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
