// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014



#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"

#include<vector>
#include<unordered_map>
#include<tuple>

using namespace std;

namespace ClassProject {

    class Manager  : public ManagerInterface {
    private:

        BDD_ID ZERO = 0;
        BDD_ID ONE = 1;

        static const size_t uTableSize = 100000000000;
        static const size_t cTableSize = 100000000000;

        struct ite_key
        {
            BDD_ID first;
            BDD_ID second;
            BDD_ID third;

            bool operator==(const ite_key &other) const
            {
                return (first == other.first
                        && second == other.second
                        && third == other.third);
            }
        };

        struct uKeyHasher
        {
            BDD_ID operator()(const ite_key& k) const;
        };

        struct cKeyHasher
        {
            BDD_ID operator()(const ite_key& k) const;
        };

        struct u_tableElement {
            BDD_ID id;
            string label;
            BDD_ID high;
            BDD_ID low;
            BDD_ID topVar;

            bool operator==(const u_tableElement &other) const
            {
                return (high == other.high
                        && low == other.low
                        && topVar == other.topVar);
            }
            bool operator==(const BDD_ID &other) const
            {
                return (id == other);
            }
        };

        vector<u_tableElement> uniqueTable;
        unordered_multimap<ite_key, u_tableElement, uKeyHasher> uniqueTableCache;
        unordered_map<ite_key, BDD_ID, cKeyHasher> computedTable;

    public:

        Manager();

        ~Manager();

        void printComputedTable();

        void printUniqueTable();

        void printUniqueHashTable();

        BDD_ID createVar(const string &label) override;

        bool isInUniqueTable(BDD_ID ID);

        const BDD_ID &True() override;

        const BDD_ID &False() override;

        bool isConstant(BDD_ID f) override;

        bool isVariable(BDD_ID x) override;

        bool foundInComputedTable(ite_key &ite_k);

        bool isTerminalCase(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result);

        bool foundInUniqueTable(ite_key &ite_k);

        BDD_ID defineTopVar(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID find_or_add_uniqueTable(ite_key &u_ite_k);

        string getVarName(BDD_ID var);

        BDD_ID topVar(BDD_ID f) override;

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorTrue(BDD_ID f) override;

        BDD_ID coFactorFalse(BDD_ID f) override;

        BDD_ID neg(BDD_ID a) override;

        BDD_ID and2(BDD_ID a, BDD_ID b) override;

        BDD_ID or2(BDD_ID a, BDD_ID b) override;

        BDD_ID xor2(BDD_ID a, BDD_ID b) override;

        BDD_ID nand2(BDD_ID a, BDD_ID b) override;

        BDD_ID nor2(BDD_ID a, BDD_ID b) override;

        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

        std::string getTopVarName(const BDD_ID &root) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

        size_t uniqueTableSize() override;
    };
}

#endif




