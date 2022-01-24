
#include "Manager.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace ClassProject;
using namespace std;

Manager::Manager() {
    uniqueTable.push_back({0,"FALSE",0,0,0}); //false node
    uniqueTable.push_back({1,"TRUE",1,1,1}); //true node
    triple_key false_key = make_tuple(0,0,0);
    triple_key true_key = make_tuple(1,1,1);
    rev_unique_table.emplace(pair<triple_key, BDD_ID>(false_key,0));
    rev_unique_table.emplace(pair<triple_key, BDD_ID>(true_key,1));
    nextId = 2;
}
string Manager::getVarName(BDD_ID var){
    return uniqueTable[var].label;
}
void Manager::printRevUniqueTable(){
    cout << "ID"
         << setw(10)
         << "TopVar"
         << setw(10)
         << "High"
         << setw(10)
         << "Low"
         << endl;
    for (auto &it : rev_unique_table) {
        cout << (it.second)
             << setw(10)
             << get<0>(it.first)
             << setw(10)
             << get<1>(it.first)
             << setw(10)
             << get<2>(it.first)
             << endl;
    }
}
void Manager::printUniqueTable(){
    cout <<  "ID"
         << setw(20)
         << "Label"
         << setw(10)
         << "High"
         << setw(10)
         << "Low"
         << setw(10)
         << "Top var"
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

//void Manager::getCopyOfUniqueTable(vector<u_tableElement> &copyUniqueTable){
//    for(auto &it : uniqueTable){
//        copyUniqueTable.push_back(it);
//    }
//}

/**
 * @brief Implementation of 'createVar' function,
 * The function creates a variable with the given name and
 * adds it to the unique table.
 * @params A string which is the name of variable to be created.
 * @retval Returns the id of the variable that it creates.
 */
BDD_ID Manager::createVar(const string &label){
        uniqueTable.push_back({nextId,label,1,0,nextId});
        triple_key key = make_tuple(nextId,1,0);
        rev_unique_table.emplace(pair<triple_key, BDD_ID>(key,nextId));
        nextId++;
        return nextId;
}

//checks if the variable already exists in the uniqueTable with this specific label
//bool Manager::varExists(const string &label){
//    for(auto &j: uniqueTable){
//        if(j.label == label){
//           return true;
//        }
//    }
//    return false;
//}
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


bool Manager::foundInComputedTable(triple_key ite_k){
    return computedTable.count(ite_k);
}

bool Manager::foundInUniqueTable(triple_key unique_key){
    return rev_unique_table.count(unique_key);
}
//BDD_ID Manager::foundInUniqueTable(unique_key uniqueKey){
//   auto it = rev_unique_table.find(uniqueKey);
//   if(it!=rev_unique_table.end())
//       return it->second;
//   else
//       return -1;
//}


bool Manager::isTerminalCase(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result) const{
    //Check if terminal case
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

BDD_ID Manager::find_or_add_uniqueTable(BDD_ID topVar, BDD_ID rHigh, BDD_ID rLow){
    triple_key key = make_tuple(topVar,rHigh,rLow);
    if(foundInUniqueTable(key)){
        rev_unique_table[key];
    }
    else{
        BDD_ID id = nextId++;
        uniqueTable.push_back({id,nextLabel,rHigh,rLow,topVar});
        rev_unique_table.emplace(pair<triple_key, BDD_ID>(key,id));
        return id;
    }

}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID result;
    BDD_ID topVarTmp, rHigh, rLow;
    triple_key ite_k = make_tuple(i,t,e);
    if(isTerminalCase(i, t, e, result))
        //! If it is a terminal case
        return result;
    else if (!computedTable.empty() && foundInComputedTable(ite_k)) {
        //! check if computed table is not empty and if result is already computed
        result = computedTable[ite_k];
        return result;
    }
    else{
        //! If not terminal case and not in computed table
        topVarTmp = defineTopVar(i,t,e);

        rHigh = ite(coFactorTrue(i, topVarTmp), coFactorTrue(t,topVarTmp), coFactorTrue(e, topVarTmp));
        rLow = ite(coFactorFalse(i, topVarTmp), coFactorFalse(t,topVarTmp), coFactorFalse(e, topVarTmp));

        if(rHigh == rLow) {
            computedTable.emplace(pair<triple_key, BDD_ID>(ite_k,rHigh));
            return rHigh;
        }

        result = find_or_add_uniqueTable(topVarTmp, rHigh, rLow);
        computedTable.emplace(pair<triple_key, BDD_ID>(ite_k,result));
        return result;
    }
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
}

BDD_ID Manager::coFactorFalse(BDD_ID f){
    return uniqueTable[f].low;
}

BDD_ID Manager::neg(BDD_ID a){
    nextLabel = "("+getVarName(a)+")'";
    BDD_ID result = ite(a, zero ,one);
    return result;
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    nextLabel = getVarName(a)+"*"+getVarName(b);
    BDD_ID result = ite(a, b ,zero);
    return result;
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    nextLabel = getVarName(a)+"+"+getVarName(b);
    BDD_ID result = ite(a, one ,b);
    return result;
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"x"+getVarName(b)+")'";
    BDD_ID neg_b_id = neg(b);
    BDD_ID result = ite(a, neg_b_id ,b);
    return result;
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"*"+getVarName(b)+")'";
    BDD_ID neg_b_id = neg(b);
    BDD_ID result = ite(a, neg_b_id ,one);
    return result;
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"+"+getVarName(b)+")'";
    BDD_ID neg_b_id = neg(b);
    BDD_ID result = ite(a, zero ,neg_b_id);
    return result;
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"x"+getVarName(b)+")'";
    BDD_ID neg_b_id = neg(b);
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
    nodes_of_root.emplace(root);

    if(root_high == root_low)
        return;
    else {
        findNodes(root_low,nodes_of_root);
        findNodes(root_high,nodes_of_root);
    }

}
//Emplace it does in-place insertion and avoids an unnecessary copy of object.
void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    set <BDD_ID> nodes_from_root;
    findNodes(root, nodes_from_root);
    auto it = next(nodes_from_root.begin(), 2);
    while( it != nodes_from_root.end()) {
        vars_of_root.emplace(topVar(*it));
        ++it;
    }
}

//Returns the number of nodes currently existing in the unique table of the Manager class.
size_t Manager::uniqueTableSize(){
   return uniqueTable.size();
}



