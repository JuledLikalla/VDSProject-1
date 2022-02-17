//
// Created by tobias on 29.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include <iostream>
#include "Reachability.h"
#include <vector>
using namespace ClassProject;
using namespace std;


//struct ReachabilityTest : testing::Test{
//    Reachability stateMachine;
//    vector<BDD_ID> states = stateMachine.getStates();
//    std::vector<BDD_ID> functions;
//    BDD_ID s0 = states.at(0);
//    BDD_ID s1 = states.at(1);
//};

struct ManagerTest : testing::Test{



};

TEST(managerTest, TwoVariableStateMachine) {
    ClassProject::Reachability stateMachine(2);
    vector<BDD_ID> states = stateMachine.getStates();
    vector<BDD_ID> tFunction;
    BDD_ID s0 = states.at(0);
    BDD_ID s1 = states.at(1);
    tFunction.push_back(stateMachine.neg(s0));
    tFunction.push_back(stateMachine.neg(s1));
    stateMachine.setTransitionFunctions(tFunction);
    stateMachine.setInitState({false,false});

    EXPECT_TRUE(stateMachine.isReachable({true,true}));
    EXPECT_TRUE(stateMachine.isReachable({false,false}));
    EXPECT_FALSE(stateMachine.isReachable({true,false}));
    EXPECT_FALSE(stateMachine.isReachable({false,true}));

}

TEST(managerTest, ThreeVariableStateMachine) {
    ClassProject::Reachability stateMachine(3);
    vector<BDD_ID> states = stateMachine.getStates();
    vector<BDD_ID> tFunction;
    BDD_ID s0 = states.at(0);
    BDD_ID s1 = states.at(1);
    BDD_ID s2 = states.at(2);
    tFunction.push_back(stateMachine.and2(s1, s2));
    tFunction.push_back(stateMachine.or2(s0, s2));
    tFunction.push_back(stateMachine.neg(s1));

    stateMachine.setTransitionFunctions(tFunction);
    stateMachine.setInitState({false,false,false});


    ASSERT_TRUE(stateMachine.isReachable({false, false, false}));
    ASSERT_TRUE(stateMachine.isReachable({false, false, true}));
    ASSERT_TRUE(stateMachine.isReachable({false, true, false}));
    ASSERT_TRUE(stateMachine.isReachable({false, true, true}));
    ASSERT_FALSE(stateMachine.isReachable({true, false, false}));
    ASSERT_FALSE(stateMachine.isReachable({true, false, true}));
    ASSERT_TRUE(stateMachine.isReachable({true, true, false}));
    ASSERT_FALSE(stateMachine.isReachable({true, true, true}));
}

#endif
