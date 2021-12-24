// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014



#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include<vector>
#include<stack>
using namespace std;

#define zero static_cast<BDD_ID>(0)
#define one static_cast<BDD_ID>(1)
#define smallestVarId static_cast<BDD_ID>(2)


namespace ClassProject {
    class Manager  : public ManagerInterface {
    public:
        struct u_tableElement {
            BDD_ID id;
            string label;
            BDD_ID high;
            BDD_ID low;
            BDD_ID topVar;
        };

        struct c_tableElement {
            BDD_ID i;
            BDD_ID t;
            BDD_ID e;
            BDD_ID result;
        };

        vector<u_tableElement> uniqueTable;
        vector<c_tableElement> computedTable;
        vector<char> operations;
        int nextId;
        string nextLabel = "";

        Manager();
        BDD_ID createVar(const string &label);
        const BDD_ID &True();
        const BDD_ID &False();
        void useExpression(string ex);
        void charCheck(char input_char);
        bool isConstant(BDD_ID f);
        bool isVariable(BDD_ID x);
        bool foundInComputedTable(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result);
        bool isTerminalCase(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result);
        bool foundInUniqueTable(BDD_ID rLow, BDD_ID rHigh, BDD_ID &r);
        BDD_ID defineTopVar(BDD_ID i, BDD_ID t, BDD_ID e);
        BDD_ID find_or_add_uniqueTable(BDD_ID topVar, BDD_ID rHigh, BDD_ID rLow);
        string getVarName(BDD_ID var);
         BDD_ID topVar(BDD_ID f);

         BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

         BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);

         BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);

         BDD_ID coFactorTrue(BDD_ID f);

         BDD_ID coFactorFalse(BDD_ID f);

         BDD_ID neg(BDD_ID a);

         BDD_ID and2(BDD_ID a, BDD_ID b);

         BDD_ID or2(BDD_ID a, BDD_ID b);

         BDD_ID xor2(BDD_ID a, BDD_ID b);

         BDD_ID nand2(BDD_ID a, BDD_ID b);

         BDD_ID nor2(BDD_ID a, BDD_ID b);

         BDD_ID xnor2(BDD_ID a, BDD_ID b);

         std::string getTopVarName(const BDD_ID &root);

         void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

         void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

         size_t uniqueTableSize();

    };
}

#endif




