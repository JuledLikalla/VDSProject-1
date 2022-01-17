
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

void Manager::printUniqueTable(){
    cout <<  "ID  " <<"Label     " << "High  " << "Low  " << "Topvar  " << endl;
    for (auto &it : uniqueTable) {
        cout << it.id << "  " << it.label << "     " << it.high << " " << it.low << " " << it.topVar << endl;
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
    u_tableElement node;
    if(!varExists(label)) {
        node.label = label;
        node.id = nextId;
        node.low = uniqueTable[0].id;
        node.high = uniqueTable[1].id;
        node.topVar = nextId;
        uniqueTable.push_back(node);
        nextId++;
        return node.id;
    }
    else
        return -1;
}
//checks if the variable already exists in the uniqueTable with this specific label
bool Manager::varExists(const string &label){
    for(auto &j: uniqueTable){
        if(j.label == label){
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

bool Manager::foundInComputedTable(vector<BDD_ID> ite_key, BDD_ID &result){
    auto it = computedTable.find(ite_key);
    if(it != computedTable.end())
    {
        result = it->second;
        return true;
    }
    return false;
}

bool Manager::foundInUniqueTable(BDD_ID rLow, BDD_ID rHigh, BDD_ID topVar, BDD_ID &r){
    for(auto & it : uniqueTable){
        if(it.low == rLow && it.high == rHigh && it.topVar == topVar){
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

    if(foundInUniqueTable(rLow, rHigh, topVar, r))
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
    vector<BDD_ID> ite_key = {i,t,e};
    if(isTerminalCase(i, t, e, result))
        //! If it is a terminal case
        return result;
    else if (!computedTable.empty() && foundInComputedTable(ite_key, result))
        //! check if computed table is not empty and if result is already computed
        return result;
    else{
        //! If not terminal case and not in computed table
        topVarTmp = defineTopVar(i,t,e);

       rHigh = ite(coFactorTrue(i, topVarTmp), coFactorTrue(t,topVarTmp), coFactorTrue(e, topVarTmp));
       rLow = ite(coFactorFalse(i, topVarTmp), coFactorFalse(t,topVarTmp), coFactorFalse(e, topVarTmp));

        if(rHigh == rLow) {
            computedTable.insert(pair<vector<BDD_ID>, BDD_ID>(ite_key,rHigh));
            return rHigh;
        }

        result = find_or_add_uniqueTable(topVarTmp, rHigh, rLow);
        computedTable.insert(pair<vector<BDD_ID>, BDD_ID>(ite_key,result));
        return result;
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    BDD_ID high = uniqueTable[f].high;
    BDD_ID low = uniqueTable[f].low;
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
    BDD_ID high = uniqueTable[f].high;
    BDD_ID low = uniqueTable[f].low;
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
    BDD_ID high = uniqueTable[f].high;
    BDD_ID low = uniqueTable[f].low;

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
    BDD_ID high = uniqueTable[f].high;
    BDD_ID low = uniqueTable[f].low;

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
    for(auto &i: uniqueTable ){
       if( i.id == root){
           return uniqueTable[i.topVar].label;
       }
    }
    return "";
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



