#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#ifndef LAB4_EXTRAFILE_H
#define LAB4_EXTRAFILE_H

using namespace std;

class NewFile {
    string fileName = "";
    int dataSize = 0;
    vector<string> numVect;
    vector<string> themeVect;
    vector<string> nameVect;
    vector<int> miniFigVect;
    vector<int> pieceVect;
    vector<double> priceVect;

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
//        bool CombineSave(NewFile fileArray[], int size);
        // Getters
        int GetSize();
//        bool CombineSave(NewFile fileArray[]);
//        vector<string>* GetNumVect() const;
//        vector<string>* GetThemeVect() const;
//        vector<string>* GetNameVect() const;
//        vector<int>* GetMiniVect() const;
//        vector<int>* GetPieceVect() const;
//        vector<double>* GetPriceVect() const;
        void PrintAll(int i) const;
        // Tasks
        void MostExpensive();
        void MostPieces();
        void SearchName(string searcher);
        void SearchThemes(string themeSearcher);
        void AveParts();
        void PriceInfo();
        void MiniInfo();
        void BoughtAll();

};


#endif //LAB4_EXTRAFILE_H
