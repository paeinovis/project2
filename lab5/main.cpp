#include <iomanip>
#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
    string file1 = "friendlyships.shp";
    string file2 = "enemyships.shp";
    bool success = false;
    NewFile loadedFile;

    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    switch (option) {
        case 1: {
            loadedFile = NewFile(file1);
            success = loadedFile.LoadAndSave();
            break;
        }
        case 2: {
            loadedFile = NewFile(file2);
            success = loadedFile.LoadAndSave();
            break;
        }
        case 3: {
            string comFiles[2] = {file1, file2};
            loadedFile = NewFile("all.shp");
            success = loadedFile.CombineSave(comFiles);
            break;
        }
        default: {
            cout << "Something went wrong.\n";
        }
    }

    if (!success) {
        cout << endl << "Something went wrong.\n";
    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;
    cout << "6. Print test" << endl;

    int choice;
    cin >> choice;
    cin.get();  // Clear newline character for any later input

    switch(choice){
        case 1: {       // Print all ships
            loadedFile.PrintAllShips();
            break;
        }
        case 2: {       // Print starship with the most powerful weapon
            loadedFile.StrongestWeapon();
            break;
        }
        case 3: {       // Print most powerful ship overall
            loadedFile.StrongestShip();
            break;
        }
        case 4: {       // Print the weakest ship
            loadedFile.WeakestShip();
            break;
        }
        case 5: {       // Print unarmed ships
            loadedFile.UnarmedShips();
            break;
        }
        case 6: {
            loadedFile.PrintTest();
            break;
        }
        default: {
            cout << "Not a valid number.";
            break;
        }
    }
    return 0;
}