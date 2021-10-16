#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

int main()
{
    cout << "1. Random Numbers\n";
    cout << "2. State Info\n";

    int option;
    cin >> option;


    if (option == 1)
    {
        map<int, int> diceMap;

        int randomSeed;
        cout << "Random seed value: ";
        cin >> randomSeed;
        random_mt.seed(randomSeed);

        int numRolls;
        cout << "Number of times to roll the die: ";
        cin >> numRolls;

        int numSides;
        cout << "Number of sides on this die: ";
        cin >> numSides;

        for (int i = 1; i <= numSides; i++){
            diceMap[i] = 0;
        }

        int numToAdd;
        int tempValue;
        for (int i = 0; i < numRolls; i++){
            numToAdd = Random(1, numSides);
            tempValue = diceMap[numToAdd];
            diceMap[numToAdd] = tempValue + 1;
        }

        auto iter = diceMap.begin();

        for (; iter != diceMap.end(); iter++){
            cout << iter->first << ": ";
            cout << iter->second << endl;
        }
    }
    else if (option == 2)
    {
        ifstream inFS;
        string fileName = R"(C:\Users\Pae\Documents\Pictures.2\school\school but less important files\programming\projects\prog2\lab7\states.csv)";
        inFS.open(fileName, ios_base::binary);

        //  if (inFS.is_open()) {
        //       cout << "File " + fileName + " opened successfully.\n";
        //  }
        //  else {
        //       cout << "File " + fileName + " failed to open.\n";
        //       exit (EXIT_FAILURE);
        //  }

        struct State {
            string stateName;
            int perCapInc = 0;
            int pop = 0;
            int medHouseInc = 0;
            int numHouse = 0;
        };

        map<string, State> statesMap;

        int numCol = 5;
        string currentLine;
        ifstream file(fileName);
        for (int j = 0; j < numCol - 1; j++) {
            getline(file, currentLine, ',');
        }                  // Skipping the first line which is the column headers

        getline(file, currentLine);

        while (!file.eof()) {
            State currentState;

            vector<string> stringArray;

            for (int i = 0; i < numCol; i++) {
                if (i == numCol - 1) {
                    getline(file, currentLine);
                } else {
                    getline(file, currentLine, ',');
                }
                stringArray.push_back(currentLine);
            }

            string stateName = stringArray[0];
            int perCapInc, pop, medHouseInc, numHouse;
            perCapInc = pop = medHouseInc = numHouse = 0;

            try {
                perCapInc = stoi(stringArray[1]);
            } catch (const invalid_argument &e) {
            }
            try {
                pop = stoi(stringArray[2]);
            } catch (const invalid_argument &e) {
            }
            try {
                medHouseInc = stoi(stringArray[3]);
            } catch (const invalid_argument &e) {
            }
            try {
                numHouse = stoi(stringArray[4]);
            } catch (const invalid_argument &e) {
            }

            currentState.stateName = stateName;
            currentState.perCapInc = perCapInc;
            currentState.pop = pop;
            currentState.medHouseInc = medHouseInc;
            currentState.numHouse = numHouse;

            if (!stateName.empty()){
                statesMap[stateName] = currentState;
            }
        }

        cout << "1. Print all states\n";
        cout << "2. Search for a state\n";

        int userInput2;
        cin >> userInput2;

        if (userInput2 == 1){
            auto iter = statesMap.begin();

            for (; iter != statesMap.end(); iter++) {
                cout << iter->first << endl;
                cout << "Population: " << iter->second.pop << endl;
                cout << "Per Capita Income: " << iter->second.perCapInc << endl;
                cout << "Median Household Income: " << iter->second.medHouseInc << endl;
                cout << "Number of Households: " << iter->second.numHouse << endl;
            }
        }
        else if (userInput2 == 2){
            // cout << "String to search: ";
            string userString;
            getline(cin >> ws, userString);

            int count = statesMap.count(userString);
            if (count == 0){
                cout << "No match found for " << userString;
            }
            else {
                cout << userString << endl;
                cout << "Population: " << statesMap.find(userString)->second.pop << endl;
                cout << "Per Capita Income: " << statesMap.find(userString)->second.perCapInc << endl;
                cout << "Median Household Income: " << statesMap.find(userString)->second.medHouseInc << endl;
                cout << "Number of Households: " << statesMap.find(userString)->second.numHouse << endl;
            }
        }
        else {
            cout << "Not a valid number.";
        }
    }
    else {
        cout << "Not a valid number.";
    }
    return 0;
}

