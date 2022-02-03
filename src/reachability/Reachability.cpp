//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

using namespace ClassProject;

Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {
    this->stateSize = stateSize;
    for(auto i =0; i<stateSize; i++){
        states.push_back(createVar("s"+to_string(i)));
        next_states.push_back(createVar("s`"+ to_string(i)));
    }
}
