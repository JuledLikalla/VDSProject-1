
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
    BDD_ID c_and_d_id = manager.and2(c_id,d_id);
    BDD_ID f1_id = manager.or2(a_and_b_id,c_or_d_id);
};

/**
 * 'createVar' function tests
 */
TEST_F(ManagerTest, CreateVarTest){
    EXPECT_EQ(manager.False(),0);
    EXPECT_EQ(manager.True(),1);
    EXPECT_EQ(manager.createVar("a"),-1);
    EXPECT_EQ(manager.topVar(a_id),a_id);
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
TEST_F(ManagerTest,isVariableTest){
    EXPECT_FALSE(manager.isVariable(false_id));
    EXPECT_FALSE(manager.isVariable(true_id));
    EXPECT_TRUE(manager.isVariable(a_id));
    EXPECT_TRUE(manager.isVariable(b_id));
    EXPECT_TRUE(manager.isVariable(c_id));
    EXPECT_TRUE(manager.isVariable(d_id));
    EXPECT_FALSE(manager.isVariable(a_or_b_id));
    EXPECT_FALSE(manager.isVariable(c_and_d_id));
}

/**
 * 'ite' function tests
 */
TEST_F(ManagerTest,ite) {

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
    EXPECT_EQ(manager.ite(a_id, true_id, b_id), a_or_b_id);
}

TEST_F(ManagerTest,negTest){
    EXPECT_EQ(manager.neg(false_id),true_id);
    EXPECT_EQ(manager.neg(true_id),false_id);
    EXPECT_EQ(manager.neg(a_or_b_id),a_and_b_id);
    EXPECT_EQ(manager.neg(c_and_d_id),c_or_d_id);
}

/**
 * 'coFactorTrue' function tests
 */
TEST_F(ManagerTest,coFactorTrueTest){
    EXPECT_EQ(manager.coFactorTrue(true_id),true_id);
    EXPECT_EQ(manager.coFactorTrue(false_id),false_id);

    EXPECT_EQ(manager.coFactorTrue(true_id,a_id),true_id);
    EXPECT_EQ(manager.coFactorTrue(true_id,b_id),true_id);

    EXPECT_EQ(manager.coFactorTrue(false_id,a_id),false_id);
    EXPECT_EQ(manager.coFactorTrue(false_id,b_id),false_id);

    EXPECT_EQ(manager.coFactorTrue(a_id,a_id),true_id);
    EXPECT_EQ(manager.coFactorTrue(b_id,a_id),b_id);
    EXPECT_EQ(manager.coFactorTrue(c_id,a_id),c_id);
    EXPECT_EQ(manager.coFactorTrue(d_id,a_id),d_id);

    EXPECT_EQ(manager.coFactorTrue(b_id,b_id),true_id);
    EXPECT_EQ(manager.coFactorTrue(a_id,b_id),a_id);
    EXPECT_EQ(manager.coFactorTrue(c_id,b_id),c_id);
    EXPECT_EQ(manager.coFactorTrue(d_id,d_id),true_id);

    EXPECT_EQ(manager.coFactorTrue(a_or_b_id,a_id),true_id);
    EXPECT_EQ(manager.coFactorTrue(a_or_b_id,b_id),true_id);
    EXPECT_EQ(manager.coFactorTrue(c_and_d_id,a_id),c_and_d_id);
}
TEST_F(ManagerTest,coFactorFalse){
    EXPECT_EQ(manager.coFactorFalse(true_id),true_id);
    EXPECT_EQ(manager.coFactorFalse(false_id),false_id);

    EXPECT_EQ(manager.coFactorFalse(true_id,a_id),true_id);
    EXPECT_EQ(manager.coFactorFalse(true_id,b_id),true_id);

    EXPECT_EQ(manager.coFactorFalse(false_id,a_id),false_id);
    EXPECT_EQ(manager.coFactorFalse(false_id,b_id),false_id);

    EXPECT_EQ(manager.coFactorFalse(a_id,a_id),false_id);
    EXPECT_EQ(manager.coFactorFalse(b_id,a_id),b_id);
    EXPECT_EQ(manager.coFactorFalse(c_id,a_id),c_id);
    EXPECT_EQ(manager.coFactorFalse(d_id,a_id),d_id);

    EXPECT_EQ(manager.coFactorFalse(b_id,b_id),false_id);
    EXPECT_EQ(manager.coFactorFalse(a_id,b_id),a_id);
    EXPECT_EQ(manager.coFactorFalse(c_id,b_id),c_id);
    EXPECT_EQ(manager.coFactorFalse(d_id,d_id),false_id);

    EXPECT_EQ(manager.coFactorFalse(a_or_b_id,a_id),b_id);
    EXPECT_EQ(manager.coFactorFalse(a_or_b_id,b_id),a_id);
    EXPECT_EQ(manager.coFactorFalse(c_and_d_id,a_id),c_and_d_id);
}
TEST_F(ManagerTest,topVarName){
    EXPECT_EQ(manager.getTopVarName(false_id),"FALSE");
    EXPECT_EQ(manager.getTopVarName(true_id),"TRUE");
    EXPECT_EQ(manager.getTopVarName(a_id),"a");
    EXPECT_EQ(manager.getTopVarName(b_id),"b");
    EXPECT_EQ(manager.getTopVarName(c_id),"c");
    EXPECT_EQ(manager.getTopVarName(d_id),"d");
    EXPECT_EQ(manager.getTopVarName(a_or_b_id),"a");
    EXPECT_EQ(manager.getTopVarName(c_and_d_id),"c");
    EXPECT_EQ(manager.getTopVarName(f1_id),"a");
}
#endif

