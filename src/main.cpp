#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include "Manager.h"
#include <algorithm>

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

    BDD_ID a_id = manager1.createVar("a");
    BDD_ID b_id =manager1.createVar("b");
    BDD_ID c_id =manager1.createVar("c");
    BDD_ID d_id =manager1.createVar("d");
    manager1.and2(a_id, b_id);
    manager1.and2(c_id, d_id);
    BDD_ID ite_result = manager1.ite(a_id,1,b_id);
    cout<<"ITE Result: "<< ite_result <<endl;


//
//        //randomPrint(manager1);
//        string booleanExpression ;
//        cout << "Enter a boolean expression:   ";
//        cin >> booleanExpression;
//        cout << "The value is " << booleanExpression;
//        manager1.useExpression(booleanExpression);
//

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

        for (auto & i : manager1.uniqueTable) {
            cout
                    << left
                    << setw(10)
                    << i.id
                    << left
                    << setw(10)
                    << i.label
                    << left
                    << setw(10)
                    << i.low
                    << left
                    << setw(10)
                    << i.high
                    << setw(10)
                    << i.topVar
                    << endl;
        }
    }
