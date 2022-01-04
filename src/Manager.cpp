
#include "Manager.h"
#include <algorithm>
#include <iostream>

using namespace ClassProject;
using namespace std;

Manager::Manager() {
    u_tableElement falseNode = {0,"FALSE",0,0,0};
    u_tableElement trueNode = {1,"TRUE",1,1,1};
    uniqueTable.push_back(falseNode);
    uniqueTable.push_back(trueNode);
    nextId = 2;
}

string Manager::getVarName(BDD_ID var){
    return uniqueTable[var].label;
}

/**
 * @brief Implementation of 'createVar' function,
 * The function creates a variable with the given name and
 * adds it to the unique table.
 * @params A string which is the name of variable to be created.
 * @retval Returns the id of the variable that it creates.
 */
BDD_ID Manager::createVar(const string &label){
    u_tableElement node;
    bool k = false;
    int i=0;
       while( i<uniqueTable.size()){
         if(uniqueTable[i].label==label){
             cout << uniqueTable[i].label << "Label: " <<label<<endl;
            k = true;
            break;
          }
         i++;
       }
        if(!k) {
            node.label = label;
            node.id = nextId;
            node.low = uniqueTable[0].id;
            node.high = uniqueTable[1].id;
            node.topVar = nextId;
            uniqueTable.push_back(node);
            nextId++;
       }
        return node.id;
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
    for(auto & i : uniqueTable){
        if(i.id ==f){
            return (i.high == i.low);
        }
    }
    return false;
}

/**
 * @brief Implementation of 'isVariable' function,
 * The function checks if the given id represents a variable.
 * @params The id to be checked.
 * @retval Returns true, if the given id represents a variable otherwise returns false.
 */
bool Manager:: isVariable(BDD_ID x) {
    for(auto & i : uniqueTable){
        if(i.id ==x)
            return (i.high == 1 && i.low == 0  );
    }
    return false;
}

/**
 * @brief Implementation of 'topVar' function,
 * The function gets the top variable of the node with the given id.
 * @params The id of the node of which the top variable is needed.
 * @retval Returns the top variable of the node with the given id.
 */
BDD_ID Manager::topVar(BDD_ID f){
    for(auto & i : uniqueTable){
        if(i.id == f){
            return i.topVar;
        }
    }
}

bool Manager::foundInComputedTable(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result){
    for(auto & it : computedTable){
        if(it.i == i && it.t == t && it.e == e){
            result = it.result;
            return true;
        }
    }
    return false;
}

bool Manager::foundInUniqueTable(BDD_ID rLow, BDD_ID rHigh, BDD_ID &r){
    for(auto & it : uniqueTable){
        if(it.low == rLow && it.high == rHigh){
            r = it.id;
            return true;
        }
    }
    return false;
}

bool Manager::isTerminalCase(BDD_ID i, BDD_ID t, BDD_ID e, BDD_ID &result){
    //! Check if terminal case
    if(i == one){
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
    else if (t == e){
        result = t;
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
    BDD_ID r = uniqueTableSize();

    if(foundInUniqueTable(rLow, rHigh, r))
        return r;

    uniqueTable.push_back({
        r,
        nextLabel,
        rHigh,
        rLow,
        topVar
    });
    return r;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID result;
    BDD_ID topVarTmp, rHigh, rLow;
    c_tableElement newComputedIte = {i, t, e, result};
    if(isTerminalCase(i, t, e, result))
        //! If it is a terminal case
        return result;
    else if (!computedTable.empty() && foundInComputedTable(i, t, e, result))
        //! check if computed table is not empty and if result is already computed
        return result;
    else{
        //! If not terminal case and not in computed table
        topVarTmp = defineTopVar(i,t,e);

       rHigh = ite(coFactorTrue(i, topVarTmp), coFactorTrue(t,topVarTmp), coFactorTrue(e, topVarTmp));
       rLow = ite(coFactorFalse(i, topVarTmp), coFactorFalse(t,topVarTmp), coFactorFalse(e, topVarTmp));

        if(rHigh == rLow) {
            newComputedIte.result = rHigh;
            computedTable.push_back(newComputedIte);
            return rHigh;
        }

        result = find_or_add_uniqueTable(topVarTmp, rHigh, rLow);
        return result;
    }
}
BDD_ID Manager::getHigh(BDD_ID id) {
    for (auto &i: uniqueTable) {
        if (i.id == id) {
            return i.high;
        }
    }
    return -1;
}

BDD_ID Manager::getLow(BDD_ID id) {
    for (auto &i: uniqueTable) {
        if (i.id == id) {
            return i.low;
        }
    }
    return -1;
}


BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    BDD_ID high = getHigh(f);
    BDD_ID low = getLow(f);
    if (f == 0 || f==1 || x==0 || x==1 || topVar(f)>x) {
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
    BDD_ID high = getHigh(f);
    BDD_ID low = getLow(f);
    if (f == 0 || f==1 || x==0 || x==1 || topVar(f)>x) {
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
    BDD_ID x = topVar(f);
    BDD_ID high = getHigh(f);
    BDD_ID low = getLow(f);

    if (f == 0 || f == 1 || x == 0 || x == 1 || topVar(f) > x) {
        return f;
    }
    if (topVar(f) == x) {
        return high;
    } else {
        BDD_ID T = coFactorTrue(high, x);
        BDD_ID F = coFactorTrue(low, x);
        return ite(topVar(f), T, F);
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f){
    BDD_ID high = getHigh(f);
    BDD_ID low = getLow(f);

    BDD_ID x = topVar(f);
    if (f == 0 || f==1 || x==0 || x==1 || topVar(f)>x) {
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
    BDD_ID result = ite(a, neg(b) ,b);
    return result;
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"*"+getVarName(b)+")'";
    BDD_ID result = ite(a, neg(b) ,one);
    return result;
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"+"+getVarName(b)+")'";
    BDD_ID result = ite(a, zero ,neg(b));
    return result;
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
    nextLabel = "("+getVarName(a)+"x"+getVarName(b)+")'";
    BDD_ID result = ite(a, b ,neg(b));
    return result;
}

std::string Manager::getTopVarName(const BDD_ID &root){
return "";
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
}

//Returns the number of nodes currently existing in the unique table of the Manager class.
size_t Manager::uniqueTableSize(){
   return uniqueTable.size();
}



