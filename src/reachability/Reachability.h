//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H
#include "ReachabilityInterface.h"

namespace ClassProject {
    class Reachability : public ReachabilityInterface {
        explicit Reachability(unsigned int stateSize);
        //BDD_ID xnor2(BDD_ID a, BDD_ID b);
       // const std::vector<BDD_ID> &getStates() const;
        //bool is_reachable(const std::vector<bool>& stateVector);
        //void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions);
       // void setInitState(const std::vector<bool> &stateVector);
    private:
        unsigned int stateSize;
        std::vector<BDD_ID> states;
        std::vector<BDD_ID> next_states;
    };

};
#endif
