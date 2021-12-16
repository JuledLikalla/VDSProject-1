
#include "Manager.h"
#include <algorithm>
#include <string.h>
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

BDD_ID Manager::createVar(const string &label){
    tableElement node;
    bool k = false;
    int i=0;
       while( i<uniqueTable.size()){
         if(uniqueTable[i].label.compare(label)==0){
             cout << uniqueTable[i].label << "Lablel: " <<label<<endl;
            k = true;
            break;
          }
         i++;
       }
        if(k==false) {
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

void Manager::useExpression(string exp){
    vector<char> v;
    copy(exp.begin(),exp.end(), back_inserter(v));

    for(auto i = v.begin();i!=v.end(); ++i){
        charCheck(*i);
    }
}

void Manager::charCheck(char input_char) {
    //it is a letter
    if ((input_char >= 65 && input_char <= 90)|| (input_char >= 97 && input_char <= 122)){
        string c(1,input_char);
        createVar(c);
    }
        // it is a number
    else if (input_char >= 48 && input_char <= 57){
    }
        // it is a  special character
    else{
    }
}

const BDD_ID & Manager::True(){
    return uniqueTable[1].id;
}
const BDD_ID & Manager::False(){
    return uniqueTable[0].id;
}


