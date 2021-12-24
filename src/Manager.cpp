
#include "Manager.h"
#include <algorithm>
#include <iostream>

using namespace ClassProject;
using namespace std;

Manager::Manager() {
    tableElement falseNode = {0,"FALSE",0,0,0};
    tableElement trueNode = {1,"TRUE",1,1,1};
    uniqueTable.push_back(falseNode);
    uniqueTable.push_back(trueNode);
    nextId = 2;
}

/**
 * @brief Implementation of 'createVar' function,
 * The function creates a variable with the given name and
 * adds it to the unique table.
 * @params A string which is the name of variable to be created.
 * @retval Returns the id of the variable that it creates.
 */
BDD_ID Manager::createVar(const string &label){
    tableElement node;
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
    for (auto &i: uniqueTable) {
        return (i.id == x);
    }
    return false;
}

/**
 * @brief Implementation of 'topVar' function,
 * The function gets the top variable of the node with the given id.
 * @params The id of the node of which the top variable is needed.
 * @retval Return the top variable id of the node with the given id.
 */
BDD_ID Manager::topVar(BDD_ID f){
    return uniqueTable[f].topVar;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
return 1;
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
return 1;
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
return 1;
}

BDD_ID Manager::coFactorTrue(BDD_ID f){
return 1;
}

BDD_ID Manager::coFactorFalse(BDD_ID f){
return 1;
}

BDD_ID Manager::neg(BDD_ID a){
return 1;
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
return 1;
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
return 1;
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
return 1;
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
return 1;
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
return 1;
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
return 1;
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



