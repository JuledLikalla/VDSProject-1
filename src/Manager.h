// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014



#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"

#include<vector>
#include<unordered_map>
#include<boost/functional/hash.hpp>

using namespace std;

namespace ClassProject {

    class Manager  : public ManagerInterface {
    private:
        typedef tuple<BDD_ID, BDD_ID, BDD_ID> ite_key;

        struct u_tableElement {
            BDD_ID id;
            string label;
            BDD_ID high;
            BDD_ID low;
            BDD_ID topVar;
        };

        vector<u_tableElement> uniqueTable;
        unordered_map<ite_key, BDD_ID, boost::hash<ite_key>> computedTable;

        BDD_ID nextId;

        BDD_ID zero = 0;
        BDD_ID one = 1 ;
        string nextLabel;

    public:

        Manager();

        BDD_ID createVar(const string &label);

        bool varExists(const string &label);

        void printUniqueTable();

        void getCopyOfUniqueTable(vector<u_tableElement> &copyUniqueTable);

        const BDD_ID &True();

        const BDD_ID &False();

        bool isConstant(BDD_ID f);

        bool isVariable(BDD_ID x);

        bool foundInComputedTable(ite_key ite_k, BDD_ID &result);

        bool isTerminalCase(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result);

        bool foundInUniqueTable(BDD_ID rLow, BDD_ID rHigh, BDD_ID topVar, BDD_ID &r);

        BDD_ID defineTopVar(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID find_or_add_uniqueTable(BDD_ID rHigh, BDD_ID rLow, BDD_ID topVar);

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




