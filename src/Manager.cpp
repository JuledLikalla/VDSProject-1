
#include "Manager.h"
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

using namespace ClassProject;
using namespace std;

BDD_ID Manager::cKeyHasher::operator()(const ite_key& k) const{
using std::size_t;
using std::hash;
/**
 *   Compute individual hash values for i,
 *   t and e and shift each of the with different number of bits
 *   and add the results. Finally compute the remainder of the sum
 *   on division by the table size.
 **/
return ((hash<ClassProject::BDD_ID>()(k.first) << 1)
+ (hash<ClassProject::BDD_ID>()(k.second) << 2)
+ (hash<ClassProject::BDD_ID>()(k.third) << 3))%cTableSize;
}

BDD_ID Manager::uKeyHasher::operator()(const ite_key& k) const{
    using std::size_t;
    using std::hash;

/**
 *   Compute individual hash values for high,
 *   low and topVar and shift each of the with different number of bits
 *   and add the results. Finally compute the remainder of the sum
 *   on division by the table size.
 **/

    return ((hash<ClassProject::BDD_ID>()(k.first) << 1)
            + (hash<ClassProject::BDD_ID>()(k.second) << 2)
            + (hash<ClassProject::BDD_ID>()(k.third) << 3))%uTableSize;
}

Manager::Manager() {
    u_tableElement falseNode = {0, "FALSE", 0, 0, 0};
    u_tableElement trueNode = {1, "TRUE", 1, 1, 1};
    uniqueTable.push_back(falseNode);
    uniqueTable.push_back(trueNode);
    uniqueTableCache.emplace(pair<ite_key, u_tableElement>({0, 0, 0}, falseNode));
    uniqueTableCache.emplace(pair<ite_key, u_tableElement>({1, 1, 1}, trueNode));
}

Manager::~Manager() {
    uniqueTableCache.clear();
    computedTable.clear();
    uniqueTable.clear();
}

string Manager::getVarName(BDD_ID var){
    return uniqueTable[var].label;
}

void Manager::printUniqueTable(){
    cout << "Unique table memory:"<<endl;
    cout <<  "ID"
         << setw(20)
         << "Label"
         << setw(10)
         << "High"
         << setw(10)
         << "Low"
         << setw(10)
         << "Topvar"
         << endl;
    for (auto &it : uniqueTable) {
        cout << it.id
             << setw(20)
             << it.label
             << setw(10)
             << it.high
             << setw(10)
             << it.low
             << setw(10)
             << it.topVar
             << endl;
    }
}

void Manager::printUniqueHashTable(){
    cout << "Unique table cache:"<<endl;
    cout <<  "ID"
         << setw(20)
         << "Label"
         << setw(10)
         << "High"
         << setw(10)
         << "Low"
         << setw(10)
         << "Topvar"
         << endl;
    for (auto &it : uniqueTableCache) {
        cout << it.second.id
             << setw(20)
             << it.second.label
             << setw(10)
             << it.second.high
             << setw(10)
             << it.second.low
             << setw(10)
             << it.second.topVar
             << endl;
    }
}

void Manager::printComputedTable(){
    cout << "Computed table:"<<endl;
    cout << "i"
         << setw(10)
         << "t"
         << setw(10)
         << "e"
         << setw(10)
         << "result"
         << endl;
    for (auto &it : computedTable) {
        cout << it.first.first
             << setw(10)
             << it.first.second
             << setw(10)
             << it.first.third
             << setw(10)
             << it.second
             << endl;
    }
}

void Manager::getCopyOfUniqueTable(vector<u_tableElement> &copyUniqueTable){
    for(auto &it : uniqueTable){
        copyUniqueTable.push_back(it);
    }
}

/**
 * @brief Implementation of 'createVar' function,
 * The function creates a variable with the given name and
 * adds it to the unique table.
 * @params A string which is the name of variable to be created.
 * @retval Returns the id of the variable that it creates.
 */
BDD_ID Manager::createVar(const string &label){
    ite_key u_ite_k={1,0,uniqueTableSize()};
    BDD_ID varId;
    if(varExists(label, varId)) {
        return varId;
    }
    BDD_ID ID = uniqueTableSize();
    uniqueTable.push_back({ID, label, one, zero, ID});
    uniqueTableCache.emplace(pair<ite_key,u_tableElement>(u_ite_k,{ID, label, one, zero, ID}));
    return ID;
}
//checks if the variable already exists in the uniqueTable with this specific label
bool Manager::varExists(const string &label, BDD_ID &varId){
    for(auto &j: uniqueTable){
        if(j.label == label){
            varId = j.id;
            return true;
        }
    }
    return false;
}
/**
 * @brief Implementation of 'True' function,
 * The function gets the id of the True node from the unique table.
 * @params none
 * @retval Returns the id of the True node.
 */
const BDD_ID & Manager::True(){
    return uniqueTable[1].id;
}

/**
 * @brief Implementation of 'False' function,
 * The function gets the id of the False node from the unique table.
 * @params none
 * @retval Returns the id of the False node.
 */
const BDD_ID & Manager::False(){
    return uniqueTable[0].id;
}

/**
 * @brief Implementation of 'isConstant' function,
 * The function checks whether the node with the given id is a leaf node.
 * @params The id of the node to be checked.
 * @retval Returns true, if the given ID represents a leaf node otherwise returns false.
 */
bool Manager::isConstant(const BDD_ID f){
    return (uniqueTable[f].high == uniqueTable[f].low);
}

/**
 * @brief Implementation of 'isVariable' function,
 * The function checks if the given id represents a variable.
 * @params The id to be checked.
 * @retval Returns true, if the given id represents a variable otherwise returns false.
 */
bool Manager:: isVariable(BDD_ID x) {
    return (uniqueTable[x].high == 1 && uniqueTable[x].low == 0 );
}

/**
 * @brief Implementation of 'topVar' function,
 * The function gets the top variable of the node with the given id.
 * @params The id of the node of which the top variable is needed.
 * @retval Returns the top variable of the node with the given id.
 */
BDD_ID Manager::topVar(BDD_ID f){
    return uniqueTable[f].topVar;
}

bool Manager::isTerminalCase(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result){
    //! Check if terminal case
    if(i == one || t == e){
        result = t;
        return true;
    }
    else if (i == zero){
        result = e;
        return true;
    }
    else if (t == one && e == zero){
        result = i;
        return true;
    }
    return false;
}

BDD_ID Manager::defineTopVar(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID topVar_i = topVar(i);
    BDD_ID topVar_t = topVar(t);
    BDD_ID topVar_e = topVar(e);

    //! Define the as top variable the one with smallest id.
    if(!isConstant(t)){
        if(!isConstant(e)){
            if(topVar_i <= topVar_t && topVar_i <= topVar_e)
                return topVar_i;
            else if(topVar_t <= topVar_i && topVar_t <= topVar_e)
                return topVar_t;
            else{
                return topVar_e;
            }
        }else{
            if(topVar_i <= topVar_t)
                return topVar_i;
            else
                return topVar_t;
        }
    }

    if (!isConstant(e)) {
        if (topVar_i <= topVar_e)
            return topVar_i;
        else
            return topVar_e;
    }

    return topVar_i;
}

bool Manager::foundInComputedTable(ite_key ite_k){
    return (computedTable.find(ite_k) != computedTable.end());
}

bool Manager::foundInUniqueTable(ite_key ite_k){
    return (uniqueTableCache.find(ite_k) != uniqueTableCache.end());
}

BDD_ID Manager::find_or_add_uniqueTable(ite_key u_ite_k){
    BDD_ID r = uniqueTableSize();

    if(foundInUniqueTable(u_ite_k)){
        auto valueRange = uniqueTableCache.equal_range(u_ite_k);
        for(auto &it = valueRange.first; it != valueRange.second; ++it){
            if(it->second.high == u_ite_k.first &&
               it->second.low == u_ite_k.second &&
               it->second.topVar == u_ite_k.third)
                return it->second.id;
        }
    }

    uniqueTable.push_back({
          r,
          "-",
          u_ite_k.first,
          u_ite_k.second,
          u_ite_k.third
    });

    uniqueTableCache.emplace(pair<ite_key, u_tableElement>(u_ite_k,{
            r,
            "-",
            u_ite_k.first,
            u_ite_k.second,
            u_ite_k.third
    }));

    return r;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID result;
    BDD_ID topVarTmp, rHigh, rLow;
    ite_key c_ite_key = {i,t,e};
    if(isTerminalCase(i, t, e, result))
    {
        //! If it is a terminal case
        return result;
    }
    else if (!computedTable.empty() && foundInComputedTable(c_ite_key)){
        //! check if computed table is not empty and if result is already computed
        return computedTable.at(c_ite_key);
    }

    //! If not terminal case and not in computed table
    topVarTmp = defineTopVar(i,t,e);

    rHigh = ite(coFactorTrue(i, topVarTmp), coFactorTrue(t,topVarTmp), coFactorTrue(e, topVarTmp));
    rLow = ite(coFactorFalse(i, topVarTmp), coFactorFalse(t,topVarTmp), coFactorFalse(e, topVarTmp));

    if(rHigh == rLow) {
        computedTable.emplace(pair<ite_key, BDD_ID>(c_ite_key, rHigh));
        return rHigh;
    }
    ite_key u_ite_k = {rHigh, rLow, topVarTmp};
    result = find_or_add_uniqueTable(u_ite_k);
    computedTable.emplace(pair<ite_key, BDD_ID>(c_ite_key,result));
    return result;

}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    BDD_ID high = uniqueTable[f].high;
    BDD_ID low = uniqueTable[f].low;
    if (isConstant(f) || isConstant(x) || topVar(f) > x) {
        return f ;
    }
    if (topVar(f) == x) {
        return high;
    }else{
        BDD_ID T = coFactorTrue(high , x);
        BDD_ID F = coFactorTrue(low, x);
        return ite(topVar(f), T, F);
    }
}


BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    BDD_ID high = uniqueTable[f].high;
    BDD_ID low = uniqueTable[f].low;
    if (isConstant(f) || isConstant(x) || topVar(f) > x) {
        return f ;
    }
    if (topVar(f) == x) {
        return low ;
    }else{
        BDD_ID T = coFactorFalse(high, x);
        BDD_ID  F = coFactorFalse(low, x);
        return ite(topVar(f), T, F);
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f) {
    return uniqueTable[f].high;
    //return coFactorTrue(f, topVar(f));

}

BDD_ID Manager::coFactorFalse(BDD_ID f){
    return uniqueTable[f].low;
    //return coFactorFalse(f, topVar(f));

}

BDD_ID Manager::neg(BDD_ID a){
    //nextLabel = "("+getVarName(a)+")'";
    BDD_ID result = ite(a, zero ,one);
    return result;
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    //nextLabel = getVarName(a)+"*"+getVarName(b);
    BDD_ID result = ite(a, b ,zero);
    return result;
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    //nextLabel = getVarName(a)+"+"+getVarName(b);
    BDD_ID result = ite(a, one ,b);
    return result;
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    BDD_ID neg_b_id = neg(b);
    //nextLabel = getVarName(a)+" xor "+getVarName(b);
    BDD_ID result = ite(a, neg_b_id ,b);
    return result;
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
    BDD_ID neg_b_id = neg(b);
    //nextLabel = "("+getVarName(a)+"*"+getVarName(b)+")'";
    BDD_ID result = ite(a, neg_b_id ,one);
    return result;
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    BDD_ID neg_b_id = neg(b);
    //nextLabel = "("+getVarName(a)+"+"+getVarName(b)+")'";
    BDD_ID result = ite(a, zero ,neg_b_id);
    return result;
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
    BDD_ID neg_b_id = neg(b);
    //nextLabel = "("+getVarName(a)+" xor "+getVarName(b)+")'";
    BDD_ID result = ite(a, b ,neg_b_id);
    return result;
}

std::string Manager::getTopVarName(const BDD_ID &root){
    return uniqueTable[topVar(root)].label;
}

//This function takes a node root and an empty set nodes of root.
//It returns the set of all nodes which are reachable from root including itself.
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    BDD_ID root_high = uniqueTable[root].high;
    BDD_ID root_low = uniqueTable[root].low;
    nodes_of_root.insert(root);

    if(root_high == root_low)
        return;
    else {
        findNodes(root_low,nodes_of_root);
        findNodes(root_high,nodes_of_root);
    }

}

//void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
//    set <BDD_ID> nodes_from_root;
//    findNodes(root, nodes_from_root);
//    auto it = next(nodes_from_root.begin(), 2);
//    while( it != nodes_from_root.end()) {
//        vars_of_root.insert(topVar(*it));
//        ++it;
//    }
//}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    BDD_ID root_high = uniqueTable[root].high; //1
    BDD_ID root_low = uniqueTable[root].low;//3
    if(!isVariable(root)){
        if(root_high == root_low)
            return;
        else
            vars_of_root.insert(topVar(root));
    }
    if(root_high ==1 && root_low == 0){
        vars_of_root.insert(root);
    }
    findVars(root_low,vars_of_root);
    findVars(root_high,vars_of_root);
}


//Returns the number of nodes currently existing in the unique table of the Manager class.
size_t Manager::uniqueTableSize(){
    return uniqueTable.size();
}


