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

        this->stateSize = stateSize;
        for(auto i =0; i<stateSize; i++){
            states.push_back(createVar("s"+to_string(i)));
            next_states.push_back(createVar("s`"+ to_string(i)));
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

        for(auto i=0; i<stateSize; i++){
            if (find(next_states.begin(), next_states.end(), transitionFunctions.at(i))== next_states.end())
                throw runtime_error("An unknown ID is provided!");
        }

        tFunctions = transitionFunctions;
    }
    catch (const runtime_error& e)
    {
        cout << "Runtime error: " << e.what() << endl;
    }
}

void Reachability::computeTransitionRelation(){
    std::vector<BDD_ID> taus={0};
    for(auto i=0;i<stateSize;i++){
        taus.push_back( xnor2(next_states.at(i),tFunctions.at(i)) ) ;
    }
    tau=taus.at(0);
    for(int i=0;i<stateSize;i++){
        tau=and2(tau, taus.at(i));
    }
}

BDD_ID Reachability::compute_reachable_states() {
    BDD_ID  CR;
    BDD_ID  CR_it = Cs_0;
    BDD_ID  temp1;
    BDD_ID  temp2;
    BDD_ID  img_next;
    BDD_ID img_current;
    do{
        CR = CR_it;
        temp1 = and2(CR,tau);
        for(auto i= 0; i<(stateSize-1);i++){
            temp2 = or2(coFactorTrue(temp1,states.at(i+1)), coFactorFalse(temp1, states.at(i+1)));
            img_next = or2(coFactorTrue(temp2,states.at(i)), coFactorFalse(temp2,states.at(i)));
        }
        temp1 = 1;
        for(auto i = 0; i<stateSize; i++){
            temp1 = and2(temp1, xnor2(states.at(i), next_states.at(i)));
        }
        temp1 = and2(temp1, img_next);
        for(auto i= 0; i<(stateSize-1);i++){
            temp2 = or2(coFactorTrue(temp1, next_states.at(i+1)), coFactorFalse(temp1, next_states.at(i+1)));
            img_current = or2(coFactorTrue(temp2,next_states.at(i)), coFactorFalse(temp2,next_states.at(i)));
        }
        CR_it = or2(CR,  img_current);
    } while (CR != CR_it);
    return CR;
}

void Reachability::setInitState(const std::vector<bool> &stateVector) {
    std::vector<BDD_ID> temp_BDD_ID;
    for(auto i=0;i<stateSize;i++){
        temp_BDD_ID.push_back(xnor2(states.at(i), stateVector.at(i)));
    }
    Cs_0=temp_BDD_ID.at(0);
    for(int i=1;i<stateSize;i++){
        Cs_0=and2(Cs_0, temp_BDD_ID.at(i));
    }
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
}