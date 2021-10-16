#include "extrafile.h"
#include "vector"
using namespace std;



// Constructors
NewFile::NewFile() {
    fileName = "";
}

NewFile::NewFile(string filename) {
    fileName = filename;
}
//
//// Getters
int NewFile::GetSize() {
    return dataSize;
}

//vector<string> *NewFile::GetNumVect() const {
//    return numVect;
//}
//
//vector<string> *NewFile::GetThemeVect() const {
//    return themeVect;
//}
//
//vector<string> *NewFile::GetNameVect() const {
//    return nameVect;
//}
//
//vector<int> *NewFile::GetMiniVect() const {
//    return miniFigVect;
//}
//
//vector<int> *NewFile::GetPieceVect() const {
//    return pieceVect;
//}
//
//vector<double> *NewFile::GetPriceVect() const {
//    return priceVect;
//}

void NewFile::PrintAll(int i) const {
    cout << "Name: " << nameVect.at(i) << endl;
    cout << "Number: " << numVect.at(i) << endl;
    cout << "Theme: " << themeVect.at(i) << endl;
    cout << "Price: $" << priceVect.at(i) << endl;
    cout << "Minifigures: " << miniFigVect.at(i) << endl;
    cout << "Piece count: " << pieceVect.at(i) << endl;

}

// Behavior
bool NewFile::LoadFile() {        // Attempt to open file
    inFS.open(fileName);
    bool opened = false;
    if (inFS.is_open()) {
        cout << "File " + fileName + " opened successfully.\n";
        opened = true;
    } else {
        cout << "File " + fileName + " failed to open.\n";
    }
    return opened;
}

bool NewFile::CloseFile() {       // Attempt to close currently open file
    inFS.close();
    bool closed = false;
    if (!inFS.is_open()) {
        cout << "File " + fileName + " closed successfully.\n";
        closed = true;
    } else {
        cout << "File " + fileName + " failed to close.\n";
    }
    return closed;
}

void NewFile::StoreData() {             // Store data from file
    int numCol = 6;
    string currentLine;
    ifstream file(fileName);
    for (int j = 0; j < numCol - 1; j++) {
        getline(file, currentLine, ',');
    }                  // Skipping the first line which is the column headers

    while (!file.eof()) {
        int converted;
        double doubConverted;
        vector<string> stringArray;
        for (int i = 0; i < numCol; i ++) {
            if (i == numCol - 1) {
                getline(file, currentLine);
            }
            else {
                getline(file, currentLine, ',');
            }
            stringArray.push_back(currentLine);
        }
        // numVect; int list of numbers (1st column)
            numVect.push_back(stringArray[0]);
        // themeVect; string list of names (2nd column)
            themeVect.push_back(stringArray[1]);
        // nameVect; string list of names (3rd column)
            nameVect.push_back(stringArray[2]);
        // miniFigVect; int list of numbers of mini figures (4th column)
            try {
                    converted = stoi(stringArray[3]);
                } catch (const invalid_argument& e) {
                    cout << "Could not convert mini figure string to integer.\n";
                }
            miniFigVect.push_back(converted);
        // pieceVect; int list of number of pieces (5th column)
            try {
                    converted = stoi(stringArray[4]);
                } catch (const invalid_argument& e) {
                    cout << "Could not convert piece string to integer.\n";
                }
                pieceVect.push_back(converted);
        // priceVect; double list of prices (6th column)
            try {
                    doubConverted = stof(stringArray[5]);
                } catch (const invalid_argument& e) {
                    cout << "Could not convert price string to double.\n";
                }
                priceVect.push_back(doubConverted);
        dataSize++;
    }
}



bool NewFile::LoadAndSave() {       // Loads data given a NewFile, returns false if data can't be opened
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
//
//bool NewFile::CombineSave(NewFile fileArray[]) { //FIXME
//    bool success = false;
//    for (int i = 0; i < size; i++) {
//    AB.insert(AB.end(), B.begin(), B.end());
//
//    }
//}

// Tasks

void NewFile::MostExpensive() {             // Finds the most expensive set and prints its data.
    double maxPrice = 0;
    int currentMaxIndex = 0;
    for (int i = 0; i + 1 < dataSize; i++) {
        if (maxPrice < priceVect.at(i)) {
            maxPrice = priceVect.at(i);
            currentMaxIndex = i;
        }
    }
    cout << "The most expensive set is:" << endl;
    PrintAll(currentMaxIndex);
}

void NewFile::MostPieces() {
    double maxPieceNum = 0;
    int currentMaxIndex = 0;
    for (int i = 0; i < dataSize; i++) {
        if (maxPieceNum < pieceVect.at(i)) {
            maxPieceNum = pieceVect.at(i);
            currentMaxIndex = i;
        }
    }
    cout << "Total number of sets: " << dataSize << endl;
    cout << "The set with the highest parts count:" << endl;
    PrintAll(currentMaxIndex);
}

void NewFile::SearchName(string searcher) {
    cout << "Sets matching \"" << searcher << "\":\n";
    vector<int> indeces;
    for (int i = 0; i < dataSize; i++) {
        if (nameVect[i].find(searcher) != string::npos) {
            indeces.push_back(i);
        }
    }
    if (indeces.empty()) {
        cout << "No sets found matching that search term";
    }
    else {
        for (int indece : indeces) {
            cout << numVect[indece] << " " << nameVect[indece] << " " << " $" << priceVect[indece] << endl;
        }
    }
}

void NewFile::SearchThemes(string themeSearcher) {
    vector<int> indeces;
    for (int i = 0; i < dataSize; i++) {
        if (themeVect[i].find(themeSearcher) != string::npos) {
            indeces.push_back(i);
        }
    }
    if (indeces.empty()) {
        cout << "No sets found matching that search term";
    }
    else {
        cout << "Sets matching \"" << themeSearcher << "\":\n";
        for (int indece : indeces) {
            cout << numVect[indece] << " " << nameVect[indece] << " " << themeVect[indece] << " $" << priceVect[indece] << endl;
        }
    }
}

void NewFile::AveParts() {
int aveParts;
int partsTot = 0;

for (int i = 0; i < dataSize; i++) {
    partsTot += pieceVect[i];
}

aveParts = partsTot / dataSize;

cout << "Average part count for " << dataSize << " sets:" << aveParts;
}

void NewFile::PriceInfo() {
    double maxPrice = 0;
    double minPrice = 0;
    int currentMaxIndex = 0;
    int currentMinIndex = 0;
    for (int i = 0; i < dataSize; i++) {
        if (maxPrice < priceVect.at(i)) {
            maxPrice = priceVect.at(i);
            currentMaxIndex = i;
        }
        if (minPrice > priceVect.at(i)) {
            minPrice = priceVect.at(i);
            currentMinIndex = i;
        }
    }
    int avePrice;
    int priceTot = 0;

    for (int i = 0; i < dataSize; i++) {
        priceTot += pieceVect[i];
    }

    avePrice = priceTot / dataSize;

    cout << "Average price information for " << dataSize << " sets: " << avePrice << endl;
    cout << "Set with the minimum price:\n";
    PrintAll(currentMinIndex);
    cout << "Set with the maximum price:\n";
    PrintAll(currentMaxIndex);
}

void NewFile::MiniInfo() {
    int aveMinis;
    int minisTot = 0;

    for (int i = 0; i < dataSize; i++) {
        minisTot += miniFigVect[i];
    }

    aveMinis = minisTot / dataSize;

    cout << "Average part count for " << dataSize << " sets:" << aveMinis;
}

void NewFile::BoughtAll() {
    int priceTot = 0;
    for (int i = 0; i < dataSize; i++) {
        priceTot += pieceVect[i];
    }
    int pieceTot = 0;
    for (int i = 0; i < dataSize; i++) {
        pieceTot += pieceVect[i];
    }
    int miniTot = 0;
    for (int i = 0; i < dataSize; i++) {
        miniTot += miniFigVect[i];
    }

    cout << "If you bought one of everything... \n";
    cout << "It would cost " << priceTot;
    cout << "You would have " << pieceTot << " pieces in your collection\n";
    cout << "You would have an army of " << miniTot << " minifigures!";

}


