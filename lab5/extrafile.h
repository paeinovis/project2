#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#ifndef LAB5_EXTRAFILE_H
#define LAB5_EXTRAFILE_H

using namespace std;

class NewFile {
    string fileName = "";
    vector<string> nameVect;
    vector<string> classVect;
    vector<short> lengthVect;
    vector<int> shieldCapVect;
    vector<float> maxWarpVect;

    vector<int> numWeaponsVect;
    vector<string> weapNameVect;
    vector<int> powerVect;
    vector<float> consVect;
    vector<int> indexOfWeapons;
    ifstream inFS;

public:
    // Constructors
    NewFile();
    NewFile(string filename);

    // Behaviors
private:
    void StoreData();
public:
    bool LoadFile();
    bool CloseFile();
    bool LoadAndSave();

    // Getters
    int GetSize();
    bool CombineSave(string fileArray[]);

    // Tasks
    void PrintAll(int i) const;
    void PrintAllShips();
    void PrintTest();
    void StrongestWeapon();
    void StrongestShip();
    void WeakestShip();
    void UnarmedShips();
};


#endif //LAB5_EXTRAFILE_H
