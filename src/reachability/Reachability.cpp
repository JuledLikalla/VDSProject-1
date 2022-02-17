//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"
#include<iostream>
#include <algorithm>

using namespace ClassProject;
using namespace std;


Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {

    try
    {
        if(stateSize == 0)
            throw runtime_error("stateSize is 0");
        vector<BDD_ID> initialstate;
        vector<BDD_ID> tFunctions;
        this->stateSize = stateSize;
        for(int i =0; i<stateSize; i++) {
            states.push_back(createVar("s" + to_string(i)));
        }
        for(int i =0; i<stateSize; i++) {
            next_states.push_back(createVar("s`" + to_string(i)));
            tFunctions.push_back(0);
        }
    }
    catch (const runtime_error& e)
    {
        cout << "Runtime error: " << e.what() << endl;
    }
}

const vector<BDD_ID> &Reachability::getStates() const{
    return states;
}

void Reachability::setTransitionFunctions(const vector<BDD_ID> &transitionFunctions){
    try
    {
        if(stateSize != transitionFunctions.size())
            throw runtime_error("The number of given transition functions does not match the number of state bits!");

        for(int i=0; i<stateSize; i++){
          if (!isInUniqueTable(transitionFunctions.at(i)))
              throw runtime_error("An unknown ID is provided!");
        }

        tFunctions = transitionFunctions;
    }
    catch (const runtime_error& e)
    {
        cout << "Runtime error: " << e.what() << endl;
    }
}

BDD_ID Reachability::computeTransitionRelation(){
    BDD_ID tau = 1;
    for(int i=0;i<stateSize;i++){
        tau = and2( tau,xnor2(next_states.at(i),tFunctions.at(i)) ) ;
    }
    return tau;
}

BDD_ID Reachability::compute_reachable_states() {
    BDD_ID tau = computeTransitionRelation();
    BDD_ID  CR;
    BDD_ID  CR_it = computeCs0();
    BDD_ID  img_next;
    BDD_ID img_current;
    do{
        CR = CR_it;
        img_next = computeImgNext(tau,CR);
        img_current = computeImgCurrent(img_next);
        CR_it = or2(CR,  img_current);
    } while (CR != CR_it);
    return CR;
}

ClassProject::BDD_ID ClassProject::Reachability::computeImgNext(BDD_ID tau, BDD_ID CR) {
    BDD_ID temp;
    BDD_ID imgNext;
    temp = and2(CR, tau);
    for (int i = states.size() - 1; i >= 0; i--) {
        temp = or2(coFactorTrue(temp, states[i]), coFactorFalse(temp, states[i]));
    }
    imgNext = temp;

    return imgNext;
}

ClassProject::BDD_ID ClassProject::Reachability::computeImgCurrent(BDD_ID imgNext) {
    BDD_ID imgCurrent;

    BDD_ID temp = 1;
    for(int i = 0; i<stateSize; i++){
        temp = and2(temp, xnor2(states.at(i), next_states.at(i)));
    }
    temp = and2(temp, imgNext);
    for(int i= stateSize-1; i>=0;i--){
        temp = or2(coFactorTrue(temp,next_states.at(i)), coFactorFalse(temp,next_states.at(i)));
    }
    imgCurrent = temp;
    return imgCurrent;
}

void Reachability::setInitState(const std::vector<bool> &stateVector) {
    try{
        if(stateSize != stateVector.size())
            throw runtime_error("The number of given transition functions does not match the number of state bits!");
        for (int i = 0; i < stateSize; i++) {
            if (!stateVector.at(i))
                initalStates.push_back(0);
            else
                initalStates.push_back(1);
        }
    }
    catch (const runtime_error& e)
    {
        cout << "Runtime error: " << e.what() << endl;
    }

}


BDD_ID Reachability::computeCs0() {
    BDD_ID Cs_0 = 1;
    for(int i = 0; i<stateSize; i++){
        Cs_0 = and2(Cs_0, xnor2(states[i], initalStates[i]));
   }
    return Cs_0;

}


bool Reachability::isReachable(const std::vector<bool>& stateVector){
    try
    {
        if(stateSize != stateVector.size())
            throw runtime_error("Number of states does not match with number of state bits!");
        BDD_ID C_R = compute_reachable_states();
        for(int i = 0; i < stateSize; i++) {
            if(stateVector.at(i)) {
                C_R = coFactorTrue(C_R,  states.at(i));
            } else {
                C_R = coFactorFalse(C_R,  states.at(i));
            }
        }
        if(C_R == 1)
            return true;
        else
            return false;
    }
    catch (const runtime_error& e)
    {
        cout << "Runtime error: " << e.what() << endl;
    }
    return false;
}



