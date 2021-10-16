#include "extrafile.h"
#include <vector>
#include "string"
#include <iomanip>
using namespace std;

// Constructors
NewFile::NewFile() {
    fileName = "";
}

NewFile::NewFile(string filename) {
    fileName = filename;
}

// Behavior
bool NewFile::LoadFile() {        // Attempt to open file
    inFS.open(fileName, ios_base::binary);
    bool opened = false;
    if (inFS.is_open()) {
        cout << "File " + fileName + " opened successfully.\n";
        opened = true;
    }
    else {
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
    }
    else {
        cout << "File " + fileName + " failed to close.\n";
    }
    return closed;
}

void NewFile::StoreData() {
    int count;
    int currentCount = 0;
    short currentShipLength = 0;
    string currentName;
    string currentClass;
    int currentShield = 0;
    float currentSpeed = 0;
    int currentNumWeapons = 0;
    string currentWeaponName;
    int currentPowerRating = 0;
    float currentPowerCons = 0;
    indexOfWeapons.push_back(0);

    ifstream file(fileName, ios_base::binary);

    file.read((char*)&count, 4);
    cout << "Count: " << count << endl;

    for (int i = 0; i < count; i++) {
        // Read ship name length and then get ship name from that length
        file.read((char *)&currentCount, 4);
        char* buffer = new char[currentCount];
        file.read(buffer, currentCount);
        currentName = buffer;
        nameVect.push_back(currentName);
        delete[] buffer;

        // Read ship class length and then get ship class from that length
        file.read((char *)&currentCount, 4);
        buffer = new char[currentCount];
        file.read(buffer, currentCount);
        currentClass = buffer;
        classVect.push_back(currentClass);
        delete[] buffer;

        // Get ship length
        file.read((char *)&currentShipLength, 2);
        lengthVect.push_back(currentShipLength);

        // Get ship shield
        file.read((char *)&currentShield, 4);
        shieldCapVect.push_back(currentShield);

        // Get ship speed
        file.read((char *)&currentSpeed, 4);
        maxWarpVect.push_back(currentSpeed);

        // Get num of weapons on ship
        file.read((char *)&currentNumWeapons, 4);
        numWeaponsVect.push_back(currentNumWeapons);

        // Determine if weapons present
        if (currentNumWeapons == 0) {
            numWeaponsVect.push_back(0);
            indexOfWeapons.push_back(0);
            continue;
        }
        else {
            for (int j = 0; j < currentNumWeapons; j++) {
                // Read weapon name length and then get weapon name from that length
                file.read((char *)&currentCount, 4);
                buffer = new char[currentCount];
                file.read(buffer, currentCount);
                currentWeaponName = buffer;
                weapNameVect.push_back(currentWeaponName);
                delete[] buffer;

                // Get power rating for weapon (and add to total power)
                file.read((char *) &currentPowerRating, 4);
                powerVect.push_back(currentPowerRating);

                // Get power consumption for weapon
                file.read((char *) &currentPowerCons, 4);
                consVect.push_back(currentPowerCons);

                indexOfWeapons.push_back((int) weapNameVect.size() + 1);
            }
        }
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

bool NewFile::CombineSave(string fileArray[]) {
    bool success = false;
    vector<string> tempNameVect;
    vector<string> tempClassVect;
    vector<short>tempLengthVect;
    vector<int> tempShieldCapVect;
    vector<float> tempMaxWarpVect;

    vector<int> tempNumWeaponsVect;
    vector<string> tempWeapNameVect;
    vector<int> tempPowerVect;
    vector<float> tempConsVect;
    vector<int> tempIndexOfWeapons;

    for (int i = 0; i < 2; i++) {
        NewFile currentFile = NewFile(fileArray[i]);
        success = currentFile.LoadAndSave();
        if (!success){
            return success;
        }
        else{
            if (i == 0){
                tempNameVect = currentFile.nameVect;
                tempClassVect = currentFile.classVect;
                tempLengthVect = currentFile.lengthVect;
                tempShieldCapVect = currentFile.shieldCapVect;
                tempMaxWarpVect = currentFile.maxWarpVect;

                tempNumWeaponsVect = currentFile.numWeaponsVect;
                tempWeapNameVect = currentFile.weapNameVect;
                tempPowerVect = currentFile.powerVect;
                tempConsVect = currentFile.consVect;
                tempIndexOfWeapons = currentFile.indexOfWeapons;
            }
            else{
                tempNameVect.insert(tempNameVect.end(), currentFile.nameVect.begin(), currentFile.nameVect.end());
                tempClassVect.insert(tempClassVect.end(), currentFile.classVect.begin(), currentFile.classVect.end());
                tempLengthVect.insert(tempLengthVect.end(), currentFile.lengthVect.begin(), currentFile.lengthVect.end());
                tempShieldCapVect.insert(tempShieldCapVect.end(), currentFile.shieldCapVect.begin(), currentFile.shieldCapVect.end());
                tempMaxWarpVect.insert(tempMaxWarpVect.end(), currentFile.maxWarpVect.begin(), currentFile.maxWarpVect.end());

                tempNumWeaponsVect.insert(tempNumWeaponsVect.end(), currentFile.numWeaponsVect.begin(), currentFile.numWeaponsVect.end());
                tempWeapNameVect.insert(tempWeapNameVect.end(), currentFile.weapNameVect.begin(), currentFile.weapNameVect.end());
                tempPowerVect.insert(tempPowerVect.end(), currentFile.powerVect.begin(), currentFile.powerVect.end());
                tempConsVect.insert(tempConsVect.end(), currentFile.consVect.begin(), currentFile.consVect.end());
                tempIndexOfWeapons.insert(tempIndexOfWeapons.end(), currentFile.indexOfWeapons.begin(), currentFile.indexOfWeapons.end());
            }
        }
    }
    nameVect = tempNameVect;
    classVect = tempClassVect;
    lengthVect = tempLengthVect;
    shieldCapVect = tempShieldCapVect;
    maxWarpVect = tempMaxWarpVect;

    numWeaponsVect = tempNumWeaponsVect;
    weapNameVect = tempWeapNameVect;
    powerVect = tempPowerVect;
    consVect = tempConsVect;
    indexOfWeapons = tempIndexOfWeapons;
    return success;
}


// Tasks
void NewFile::PrintAll(int i) const {
    int numWeapons = numWeaponsVect.at(i);
    cout << "Name: " << nameVect.at(i) << endl;
    cout << "Class: " << classVect.at(i) << endl;
    cout << "Length: " << lengthVect.at(i) << endl;
    cout << "Shield capacity: " << shieldCapVect.at(i) << endl;
    cout << "Maximum Warp: " << maxWarpVect.at(i) << endl;
    cout << "Armaments: " << endl;
    int totalFirePower = 0;
    if (numWeapons == 0) {
        cout << "Unarmed" << endl << endl;
    }
    else {
        for (int j = 0; j < numWeapons; j++) {
            cout << weapNameVect.at(indexOfWeapons.at(i) + j) << ", ";
            cout << powerVect.at(indexOfWeapons.at(i) + j) << ", ";
            cout << consVect.at(indexOfWeapons.at(i) + j) << endl;
            totalFirePower += powerVect.at(indexOfWeapons.at(i) + j);
        }
        cout << "Total firepower: " << totalFirePower << endl << endl;
    }
}

void NewFile::PrintAllShips() {
    for (int i = 0; i < (int) nameVect.size(); i++){
        PrintAll(i);
    }
}

void NewFile::PrintTest() {
    for (auto & i : indexOfWeapons) {
        cout << indexOfWeapons.at(i) << endl;
    }
}

void NewFile::StrongestWeapon() {
    int maxPower = 0;
    int currentMaxIndex = 0;
    for (int i = 0; i < (int) nameVect.size(); i++) {
        int numWeapons = numWeaponsVect[i];
        if (numWeapons == 0) {
            continue;
        } else {
            for (int j = 0; j < numWeapons; j++) {
                if (maxPower < powerVect.at(indexOfWeapons.at(i) + j)) {
                    maxPower = powerVect.at(indexOfWeapons.at(i) + j);
                    currentMaxIndex = i;
                }
            }
        }
    }
    cout << "The ship with the most powerful weapon is:" << endl;
    PrintAll(currentMaxIndex);
}

void NewFile::StrongestShip() {
    int maxPower = 0;
    int currentMaxIndex = 0;
    for (int i = 0; i < (int) nameVect.size(); i++) {
        int numWeapons = numWeaponsVect[i];
        if (numWeapons == 0) {
            continue;
        } else {
            int currentTotalPower = 0;
            for (int j = 0; j < numWeapons; j++) {
                currentTotalPower += powerVect.at(indexOfWeapons.at(i) + j);
            }
            if (maxPower < currentTotalPower) {
                maxPower = currentTotalPower;
                currentMaxIndex = i;
            }
        }
    }
    cout << "The most powerful ship is:" << endl;
    PrintAll(currentMaxIndex);
}

void NewFile::WeakestShip() {
    int minPower = 0;
    int currentMinIndex = 0;
    for (int i = 0; i < (int) nameVect.size(); i++) {
        int numWeapons = numWeaponsVect[i];
        if (numWeapons == 0) {
            continue;
        } else {
            for (int j = 0; j < numWeapons; j++) {
                if (minPower > powerVect.at(indexOfWeapons.at(i) + j)) {
                    minPower = powerVect.at(indexOfWeapons.at(i) + j);
                    currentMinIndex = i;
                }
            }
        }
    }
    cout << "The weakest ship is:" << endl;
    PrintAll(currentMinIndex);
}

void NewFile::UnarmedShips() {
    vector<int> unarmedShipIndeces;
    for (int i = 0; i < (int) nameVect.size(); i++) {
        if (numWeaponsVect.at(i) == 0) {
            unarmedShipIndeces.push_back(i);
        }
    }
    for (int i = 0; i < (int) unarmedShipIndeces.size(); i++) {
        PrintAll(i);
    }
}
