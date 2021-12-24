
#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include <string>
#include "../Manager.h"
#include <iostream>
using namespace ClassProject;
using namespace std;

struct ManagerTest : testing::Test{
    Manager manager;

    BDD_ID false_id = manager.False();
    BDD_ID true_id = manager.True();
    BDD_ID a_id = manager.createVar("a");
    BDD_ID b_id = manager.createVar("b");
    BDD_ID c_id = manager.createVar("c");
    BDD_ID d_id = manager.createVar("d");
    BDD_ID neg_a_id = manager.neg(a_id);
    BDD_ID neg_b_id = manager.neg(b_id);
    BDD_ID a_and_b_id = manager.and2(a_id,b_id);
    BDD_ID a_or_b_id = manager.or2(a_id,b_id);
    BDD_ID a_xor_b_id = manager.and2(a_id,b_id);
    BDD_ID a_nand_b_id = manager.nor2(a_id,b_id);
    BDD_ID a_xnor_b_id = manager.xnor2(a_id,b_id);
    BDD_ID c_or_d_id = manager.or2(c_id,d_id);
    BDD_ID f1_id = manager.or2(a_and_b_id,c_or_d_id);
};

/**
 * 'createVar' function tests
 */
TEST_F(ManagerTest, CreateVarTest){
    EXPECT_EQ(manager.False(),0);
    EXPECT_EQ(manager.True(),1);
}

/**
 * 'True' function tests
 */
TEST_F(ManagerTest, trueNodeTest){
    ASSERT_EQ(manager.True(), 1);
}

/**
 * 'false' function tests
 */
TEST_F(ManagerTest,FalseNodeTest){
    ASSERT_EQ(manager.False(), 0);
}

/**
 * 'isConstantTest' function tests
 */
TEST_F(ManagerTest,isConstantTest){
    EXPECT_TRUE(manager.isConstant(false_id));
    EXPECT_TRUE(manager.isConstant(true_id));
    EXPECT_FALSE(manager.isConstant(a_id));
    EXPECT_FALSE(manager.isConstant(b_id));
    EXPECT_FALSE(manager.isConstant(c_id));
    EXPECT_FALSE(manager.isConstant(d_id));
}

/**
 * 'topVar' function tests
 */
TEST_F(ManagerTest,topVar){
    EXPECT_EQ(manager.topVar(false_id), false_id);
    EXPECT_EQ(manager.topVar(true_id), true_id);
    EXPECT_EQ(manager.topVar(a_id), a_id);
    EXPECT_EQ(manager.topVar(b_id), b_id);
    EXPECT_EQ(manager.topVar(c_id), c_id);
    EXPECT_EQ(manager.topVar(d_id), d_id);
    EXPECT_EQ(manager.topVar(a_and_b_id), a_id);
    EXPECT_EQ(manager.topVar(c_or_d_id), c_id);
}

/**
 * 'ite' function tests
 */
TEST_F(ManagerTest,ite){

    //!Test Terminal Cases
    EXPECT_EQ(manager.ite(false_id, b_id, a_id), a_id);
    EXPECT_EQ(manager.ite(true_id, a_id, b_id), a_id);
    EXPECT_EQ(manager.ite(a_id, true_id, false_id), a_id);
    EXPECT_EQ(manager.ite(b_id, a_id, a_id), a_id);
//    EXPECT_EQ(manager.ite(a_id, false_id, true_id), manager.neg(a_id));

    EXPECT_EQ(manager.ite(false_id, d_id, c_id), c_id);
    EXPECT_EQ(manager.ite(true_id, c_id, d_id), c_id);
    EXPECT_EQ(manager.ite(c_id, true_id, false_id), c_id);
    EXPECT_EQ(manager.ite(d_id, c_id, c_id), c_id);
//    EXPECT_EQ(manager.ite(c_id, false_id, true_id), manager.neg(c_id));

    //!Other Tests

}


#endif
