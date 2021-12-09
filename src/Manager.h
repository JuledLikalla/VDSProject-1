// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014



#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include<vector>
using namespace std;

namespace ClassProject {
    class Manager {
    public:
        struct tableElement {
            BDD_ID id;
            string label;
            BDD_ID high;
            BDD_ID low;
            BDD_ID topVar;
        };
        vector<tableElement> uniqueTable;
        int nextId;

        Manager();
        BDD_ID createVar(const string &label);
        const BDD_ID &True();
        const BDD_ID &False();
        void useExpression(string ex);
        void charCheck(char input_char);

    };
}

#endif




