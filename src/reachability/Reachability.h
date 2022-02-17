//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H
#include "ReachabilityInterface.h"

namespace ClassProject {
    class Reachability : public ReachabilityInterface {
    public:
        Reachability(unsigned int stateSize);
        const std::vector<BDD_ID> &getStates() const;
        void setTransitionFunctions(const vector<BDD_ID> &transitionFunctions) ;
        BDD_ID compute_reachable_states();
        bool isReachable(const std::vector<bool>& stateVector);
        void setInitState(const std::vector<bool> &stateVector);
        BDD_ID computeTransitionRelation();
        BDD_ID computeCs0();
        BDD_ID computeImgNext(BDD_ID tau, BDD_ID CR);
        BDD_ID computeImgCurrent(BDD_ID imgNext);
    private:
        unsigned int stateSize;
        std::vector<BDD_ID> states;
        std::vector<BDD_ID> next_states;
        std::vector<BDD_ID> initalStates;
        BDD_ID tau;
        BDD_ID Cs_0;
        vector<BDD_ID> tFunctions;
    };

};
#endif
