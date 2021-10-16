#include <iomanip>
#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
    string file1 = "lego1.csv";
    string file2 = "lego2.csv";
    string file3 = "lego3.csv";
    NewFile newfile1 = NewFile(file1);
    NewFile newfile2 = NewFile(file2);
    NewFile newfile3 = NewFile(file3);
    bool success = false;
    NewFile* loadedFile;

    cout << "Which file(s) to open?\n";
    cout << "1. lego1.csv" << endl;
    cout << "2. lego2.csv" << endl;
    cout << "3. lego3.csv" << endl;
    cout << "4. All 3 files" << endl;
    int option;
    cin >> option;

    /*======= Load data from file(s) =======*/

    switch (option) {
        case 1: {
            loadedFile = &newfile1;
            success = newfile1.LoadAndSave();
            break;
        }
        case 2: {
            loadedFile = &newfile2;
            success = newfile2.LoadAndSave();
            break;
        }
        case 3: {
            loadedFile = &newfile3;
            success = newfile3.LoadAndSave();
            break;
        }
//        case 4: {
//            bool success1 = newfile1.LoadAndSave();
//            bool success2 = newfile2.LoadAndSave();
//            bool success3 = newfile3.LoadAndSave();
//            NewFile newFiles[3] = {&newfile1, newfile2, newfile3};
//
//            NewFile fileArray[3] = {newfile1, newfile2, newfile3};
//            if (success1 & success2 & success3){
//                success = true;
//            }
//            else {
//                success = false;
//            }
//            break;
//        }
        default: {
            cout << "Something went wrong.\n";
        }
    }

    if (!success) {
        cout << endl << "Something went wrong.\n";
    }
    else {
        cout << "Load Successful.\n";
    }
    cout << "1. Most Expensive set" << endl;
    cout << "2. Largest piece count" << endl;
    cout << "3. Search for set name containing..." << endl;
    cout << "4. Search themes..." << endl;
    cout << "5. Part count information" << endl;
    cout << "6. Price information" << endl;
    cout << "7. Minifigure information" << endl;
    cout << "8. If you bought one of everything..." << endl;
    cout << "0. Exit" << endl;
    cout << "Total number of sets: " << loadedFile->GetSize() << endl;

    int choice;
    cin >> choice;
    cin.get();  // Clear newline character for any later input

    switch(choice){
        case 1: {       // Most expensive set
            loadedFile->MostExpensive();
            break;
        }
        case 2: {       // Largest piece count
            loadedFile->MostPieces();
            break;
        }
        case 3: {       // Searches set names containing some user input
            string searcher;
            cin >> searcher;
            cin.get();
            loadedFile->SearchName(searcher);
            break;
        }
        case 4: {       // Searches set themes for some user input
            string searcher;
            cout << "Please enter set theme to be searched for: " << endl;
            cin >> searcher;
            cin.get();
            loadedFile->SearchThemes(searcher);
            break;
        }
        case 5: {       // Prints part count information
            loadedFile->AveParts();
            break;
        }
        case 6: {       // Prints price info
            loadedFile->PriceInfo();
            break;
        }
        case 7: {       // Prints minifigure information
            loadedFile->MiniInfo();
            break;
        }
        case 8: {       // Prints total price, total pieces, and total minifigures.
            loadedFile->BoughtAll();
            break;
        }
        default: {
            cout << "Not a valid number.";
            break;
        }
    }

    /*======= Print out how many sets were loaded =======*/
    /*======= Based on the choice, execute the appropriate task and show the results =======*/

    return 0;
}


