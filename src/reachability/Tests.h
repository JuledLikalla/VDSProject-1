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

TEST(managerTest, TwoVariableStateMachine) {
    ClassProject::Reachability comp(2);

    auto states = comp.getStates();
    std::vector<BDD_ID> functions;

    auto s0 = states.at(0);
    auto s1 = states.at(1);
    cout<<"s0:"<<s0<<endl;
    cout<<"s1:"<<s1<<endl;
    //s0' = not(s0)
    functions.push_back(comp.neg(s0));
    //s1' = not(s1)
    functions.push_back(comp.neg(s1));
    cout<<"s0':"<<functions.at(0)<<endl;
    cout<<"s1':"<<functions.at(1)<<endl;
    //Add transition functions
    comp.setTransitionFunctions(functions);

    EXPECT_TRUE(comp.isReachable({true,true}));
    EXPECT_TRUE(comp.isReachable({false,false}));
    EXPECT_FALSE(comp.isReachable({true,false}));
    EXPECT_FALSE(comp.isReachable({false,true}));

}

TEST(managerTest, Another_Example) {
    ClassProject::Reachability comp(3);

    auto states = comp.getStates();
    auto s0 = states.at(0);
    auto s1 = states.at(1);
    auto s2 = states.at(2);

    std::vector<BDD_ID> functions;
    functions.push_back(comp.and2(s1, s2));
    functions.push_back(comp.or2(s0, s2));
    functions.push_back(comp.neg(s1));

    comp.setTransitionFunctions(functions);

    //comp.setInitState({false, false, false});

    ASSERT_TRUE(comp.isReachable({false, false, false}));
    ASSERT_TRUE(comp.isReachable({false, false, true}));
    ASSERT_TRUE(comp.isReachable({false, true, false}));
    ASSERT_TRUE(comp.isReachable({false, true, true}));
    ASSERT_FALSE(comp.isReachable({true, false, false}));
    ASSERT_FALSE(comp.isReachable({true, false, true}));
    ASSERT_TRUE(comp.isReachable({true, true, false}));
    ASSERT_FALSE(comp.isReachable({true, true, true}));
}

#endif
