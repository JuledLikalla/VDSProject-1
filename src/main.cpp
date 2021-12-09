#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include "Manager.h"


using namespace ClassProject;

string random_string()
{
    string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    random_device rd;
    mt19937 generator(rd());

    shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str
}
void randomPrint(Manager manager1) {
    string c;
    int r;
    for (int i = 0; i < 100; i++) {
        c = random_string();           // Convert to a character from a-z
        manager1.createVar(c);
    }
    cout
            << left
            << setw(10)
            << "ID"
            << left
            << setw(5)
            << "Label"
            << left
            << setw(10)
            << "Low"
            << left
            << setw(5)
            << "High"
            << endl;

    for (int i = 0; i < 100; i++) {
        cout
                << left
                << setw(10)
                << manager1.uniqueTable[i].id
                << left
                << setw(5)
                << manager1.uniqueTable[i].label
                << left
                << setw(8)
                << manager1.uniqueTable[i].low
                << left
                << setw(5)
                << manager1.uniqueTable[i].high
                << endl;
    }
}
int main(int argc, char *argv[]) {

        Manager manager1;

        //randomPrint(manager1);
        string booleanExpression = "";
        cout << "Enter a boolean expression:   ";
        cin >> booleanExpression;
        cout << "The value is " << booleanExpression;
        manager1.useExpression(booleanExpression);

        cout
                << endl
                << left
                << setw(10)
                << "ID"
                << left
                << setw(10)
                << "Label"
                << left
                << setw(10)
                << "Low"
                << left
                << setw(10)
                << "High"
                << setw(10)
                << "Top Var"
                << endl;

        for (int i = 0; i < manager1.uniqueTable.size(); i++) {
            cout
                    << left
                    << setw(10)
                    << manager1.uniqueTable[i].id
                    << left
                    << setw(10)
                    << manager1.uniqueTable[i].label
                    << left
                    << setw(10)
                    << manager1.uniqueTable[i].low
                    << left
                    << setw(10)
                    << manager1.uniqueTable[i].high
                    << setw(10)
                    << manager1.uniqueTable[i].topVar
                    << endl;
        }

    }
