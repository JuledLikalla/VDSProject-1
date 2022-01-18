
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
    BDD_ID neg_c_id = manager.neg(c_id);
    BDD_ID neg_d_id = manager.neg(d_id);
    BDD_ID a_and_b_id = manager.and2(a_id,b_id);
    BDD_ID a_or_b_id = manager.or2(a_id,b_id);
    BDD_ID a_xor_b_id = manager.xor2(a_id,b_id);
    BDD_ID a_nand_b_id = manager.nand2(a_id,b_id);
    BDD_ID a_xnor_b_id = manager.xnor2(a_id,b_id);
    BDD_ID c_or_d_id = manager.or2(c_id,d_id);
    BDD_ID c_and_d_id = manager.and2(c_id,d_id);
    BDD_ID a_nor_b_id = manager.nor2(a_id,b_id);
    BDD_ID c_nand_d_id = manager.nand2(c_id,d_id);
    BDD_ID c_nor_d_id = manager.nor2(c_id,d_id);
    BDD_ID c_xor_d_id = manager.xor2(c_id,d_id);
    BDD_ID c_xnor_d_id = manager.xnor2(c_id,d_id);
    BDD_ID f1_id = manager.and2(a_or_b_id,c_and_d_id);

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
TEST_F(ManagerTest,iteTest){

    //!Test Terminal Cases
    EXPECT_EQ(manager.ite(false_id, b_id, a_id), a_id);
    EXPECT_EQ(manager.ite(true_id, a_id, b_id), a_id);
    EXPECT_EQ(manager.ite(a_id, true_id, false_id), a_id);
    EXPECT_EQ(manager.ite(b_id, a_id, a_id), a_id);
    EXPECT_EQ(manager.ite(a_id, false_id, true_id), neg_a_id);

    EXPECT_EQ(manager.ite(false_id, d_id, c_id), c_id);
    EXPECT_EQ(manager.ite(true_id, c_id, d_id), c_id);
    EXPECT_EQ(manager.ite(c_id, true_id, false_id), c_id);
    EXPECT_EQ(manager.ite(d_id, c_id, c_id), c_id);
    EXPECT_EQ(manager.ite(c_id, false_id, true_id), neg_c_id);

    //!Other Tests
    EXPECT_EQ(manager.ite(a_id, true_id, b_id), a_or_b_id);
    EXPECT_EQ(manager.ite(a_id, b_id, false_id), a_and_b_id);
    EXPECT_EQ(manager.ite(a_id, neg_b_id, true_id), a_nand_b_id);
    EXPECT_EQ(manager.ite(a_id, false_id, neg_b_id), a_nor_b_id);
    EXPECT_EQ(manager.ite(a_id, neg_b_id, b_id), a_xor_b_id);
    EXPECT_EQ(manager.ite(a_id, b_id, neg_b_id), a_xnor_b_id);

    EXPECT_EQ(manager.ite(c_id, true_id, d_id), c_or_d_id);
    EXPECT_EQ(manager.ite(c_id, d_id, false_id), c_and_d_id);
    EXPECT_EQ(manager.ite(c_id, neg_d_id, true_id), c_nand_d_id);
    EXPECT_EQ(manager.ite(c_id, false_id, neg_d_id), c_nor_d_id);
    EXPECT_EQ(manager.ite(c_id, neg_d_id, d_id), c_xor_d_id);
    EXPECT_EQ(manager.ite(c_id, d_id, neg_d_id), c_xnor_d_id);
    EXPECT_EQ(manager.ite(a_or_b_id, c_and_d_id,false_id), f1_id);
}

/**
 * 'neg' function tests
 */
TEST_F(ManagerTest,negTest){
    EXPECT_EQ(manager.neg(false_id),true_id);
    EXPECT_EQ(manager.neg(true_id),false_id);

    //! De Morgans Laws
    EXPECT_EQ(manager.neg(a_or_b_id),manager.and2(neg_a_id, neg_b_id));
    EXPECT_EQ(manager.neg(a_and_b_id),manager.or2(neg_a_id, neg_b_id));

    EXPECT_EQ(manager.neg(c_or_d_id),manager.and2(neg_c_id, neg_d_id));
    EXPECT_EQ(manager.neg(c_and_d_id),manager.or2(neg_c_id, neg_d_id));

    EXPECT_EQ(manager.topVar(neg_a_id), a_id);
    EXPECT_EQ(manager.topVar(neg_b_id), b_id);
    EXPECT_EQ(manager.topVar(neg_c_id), c_id);
    EXPECT_EQ(manager.topVar(neg_d_id), d_id);

    EXPECT_EQ(manager.coFactorFalse(neg_a_id), true_id);
    EXPECT_EQ(manager.coFactorTrue(neg_a_id), false_id);

    EXPECT_EQ(manager.coFactorFalse(neg_b_id), true_id);
    EXPECT_EQ(manager.coFactorTrue(neg_b_id), false_id);

    EXPECT_EQ(manager.coFactorFalse(neg_c_id), true_id);
    EXPECT_EQ(manager.coFactorTrue(neg_c_id), false_id);

    EXPECT_EQ(manager.coFactorFalse(neg_d_id), true_id);
    EXPECT_EQ(manager.coFactorTrue(neg_d_id), false_id);

}

/**
 * 'and2' function tests
 */
TEST_F(ManagerTest,and2Test){
    EXPECT_EQ(manager.and2(false_id, false_id),false_id);
    EXPECT_EQ(manager.and2(false_id, true_id),false_id);
    EXPECT_EQ(manager.and2(true_id, false_id),false_id);
    EXPECT_EQ(manager.and2(true_id, true_id),true_id);

    EXPECT_EQ(manager.and2(a_id, false_id),false_id);
    EXPECT_EQ(manager.and2(a_id, true_id),a_id);
    EXPECT_EQ(manager.and2(a_id, neg_a_id),false_id);
    EXPECT_EQ(manager.and2(a_id, a_id),a_id);

    EXPECT_EQ(manager.and2(b_id, false_id),false_id);
    EXPECT_EQ(manager.and2(b_id, true_id),b_id);
    EXPECT_EQ(manager.and2(b_id, neg_b_id),false_id);
    EXPECT_EQ(manager.and2(b_id, b_id),b_id);

    EXPECT_EQ(manager.and2(c_id, false_id),false_id);
    EXPECT_EQ(manager.and2(c_id, true_id),c_id);
    EXPECT_EQ(manager.and2(c_id, neg_c_id),false_id);
    EXPECT_EQ(manager.and2(c_id, c_id),c_id);

    EXPECT_EQ(manager.and2(d_id, false_id),false_id);
    EXPECT_EQ(manager.and2(d_id, true_id),d_id);
    EXPECT_EQ(manager.and2(d_id, neg_d_id),false_id);
    EXPECT_EQ(manager.and2(d_id, d_id),d_id);

}

/**
 * 'or2' function tests
 */
TEST_F(ManagerTest,or2Test){
    EXPECT_EQ(manager.or2(false_id, false_id),false_id);
    EXPECT_EQ(manager.or2(false_id, true_id),true_id);
    EXPECT_EQ(manager.or2(true_id, false_id),true_id);
    EXPECT_EQ(manager.or2(true_id, true_id),true_id);

    EXPECT_EQ(manager.or2(a_id, false_id),a_id);
    EXPECT_EQ(manager.or2(a_id, true_id),true_id);
    EXPECT_EQ(manager.or2(a_id, neg_a_id),true_id);
    EXPECT_EQ(manager.or2(a_id, a_id),a_id);

    EXPECT_EQ(manager.or2(b_id, false_id),b_id);
    EXPECT_EQ(manager.or2(b_id, true_id),true_id);
    EXPECT_EQ(manager.or2(b_id, neg_b_id),true_id);
    EXPECT_EQ(manager.or2(b_id, b_id),b_id);

    EXPECT_EQ(manager.or2(c_id, false_id),c_id);
    EXPECT_EQ(manager.or2(c_id, true_id),true_id);
    EXPECT_EQ(manager.or2(c_id, neg_c_id),true_id);
    EXPECT_EQ(manager.or2(c_id, c_id),c_id);

    EXPECT_EQ(manager.or2(d_id, false_id),d_id);
    EXPECT_EQ(manager.or2(d_id, true_id),true_id);
    EXPECT_EQ(manager.or2(d_id, neg_d_id),true_id);
    EXPECT_EQ(manager.or2(d_id, d_id),d_id);
}

/**
 * 'nand2' function tests
 */
TEST_F(ManagerTest,nand2Test){
    EXPECT_EQ(manager.nand2(false_id, false_id), true_id);
    EXPECT_EQ(manager.nand2(false_id, true_id), true_id);
    EXPECT_EQ(manager.nand2(true_id, false_id), true_id);
    EXPECT_EQ(manager.nand2(true_id, true_id), false_id);

    EXPECT_EQ(manager.nand2(a_id, false_id), true_id);
    EXPECT_EQ(manager.nand2(a_id, true_id), neg_a_id);
    EXPECT_EQ(manager.nand2(a_id, neg_a_id), true_id);
    EXPECT_EQ(manager.nand2(a_id, a_id), neg_a_id);

    EXPECT_EQ(manager.nand2(b_id, false_id), true_id);
    EXPECT_EQ(manager.nand2(b_id, true_id), neg_b_id);
    EXPECT_EQ(manager.nand2(b_id, neg_b_id), true_id);
    EXPECT_EQ(manager.nand2(b_id, b_id), neg_b_id);

    EXPECT_EQ(manager.nand2(c_id, false_id), true_id);
    EXPECT_EQ(manager.nand2(c_id, true_id), neg_c_id);
    EXPECT_EQ(manager.nand2(c_id, neg_c_id), true_id);
    EXPECT_EQ(manager.nand2(c_id, c_id), neg_c_id);

    EXPECT_EQ(manager.nand2(d_id, false_id), true_id);
    EXPECT_EQ(manager.nand2(d_id, true_id), neg_d_id);
    EXPECT_EQ(manager.nand2(d_id, neg_d_id), true_id);
    EXPECT_EQ(manager.nand2(d_id, d_id), neg_d_id);

}

/**
 * 'nor2' function tests
 */
TEST_F(ManagerTest,nor2Test){
    EXPECT_EQ(manager.nor2(false_id, false_id),true_id);
    EXPECT_EQ(manager.nor2(false_id, true_id),false_id);
    EXPECT_EQ(manager.nor2(true_id, false_id),false_id);
    EXPECT_EQ(manager.nor2(true_id, true_id),false_id);

    EXPECT_EQ(manager.nor2(a_id, false_id),neg_a_id);
    EXPECT_EQ(manager.nor2(a_id, true_id),false_id);
    EXPECT_EQ(manager.nor2(a_id, neg_a_id),false_id);
    EXPECT_EQ(manager.nor2(a_id, a_id),neg_a_id);

    EXPECT_EQ(manager.nor2(b_id, false_id),neg_b_id);
    EXPECT_EQ(manager.nor2(b_id, true_id),false_id);
    EXPECT_EQ(manager.nor2(b_id, neg_b_id),false_id);
    EXPECT_EQ(manager.nor2(b_id, b_id),neg_b_id);

    EXPECT_EQ(manager.nor2(c_id, false_id),neg_c_id);
    EXPECT_EQ(manager.nor2(c_id, true_id),false_id);
    EXPECT_EQ(manager.nor2(c_id, neg_c_id),false_id);
    EXPECT_EQ(manager.nor2(c_id, c_id),neg_c_id);

    EXPECT_EQ(manager.nor2(d_id, false_id),neg_d_id);
    EXPECT_EQ(manager.nor2(d_id, true_id),false_id);
    EXPECT_EQ(manager.nor2(d_id, neg_d_id),false_id);
    EXPECT_EQ(manager.nor2(d_id, d_id),neg_d_id);

}

/**
 * 'xor2' function tests
 */
TEST_F(ManagerTest,xor2Test){

    EXPECT_EQ(manager.xor2(false_id, false_id),false_id);
    EXPECT_EQ(manager.xor2(false_id, true_id),true_id);
    EXPECT_EQ(manager.xor2(true_id, false_id),true_id);
    EXPECT_EQ(manager.xor2(true_id, true_id),false_id);

    EXPECT_EQ(manager.xor2(a_id, false_id),a_id);
    EXPECT_EQ(manager.xor2(a_id, true_id),neg_a_id);
    EXPECT_EQ(manager.xor2(a_id, neg_a_id),true_id);
    EXPECT_EQ(manager.xor2(a_id, a_id),false_id);

    EXPECT_EQ(manager.xor2(b_id, false_id),b_id);
    EXPECT_EQ(manager.xor2(b_id, true_id),neg_b_id);
    EXPECT_EQ(manager.xor2(b_id, neg_b_id),true_id);
    EXPECT_EQ(manager.xor2(b_id, b_id),false_id);

    EXPECT_EQ(manager.xor2(c_id, false_id),c_id);
    EXPECT_EQ(manager.xor2(c_id, true_id),neg_c_id);
    EXPECT_EQ(manager.xor2(c_id, neg_c_id),true_id);
    EXPECT_EQ(manager.xor2(c_id, c_id),false_id);

    EXPECT_EQ(manager.xor2(d_id, false_id),d_id);
    EXPECT_EQ(manager.xor2(d_id, true_id),neg_d_id);
    EXPECT_EQ(manager.xor2(d_id, neg_d_id),true_id);
    EXPECT_EQ(manager.xor2(d_id, d_id),false_id);

}

/**
 * 'xnor2' function tests
 */
TEST_F(ManagerTest,xnor2Test){
    EXPECT_EQ(manager.xnor2(false_id, false_id),true_id);
    EXPECT_EQ(manager.xnor2(false_id, true_id),false_id);
    EXPECT_EQ(manager.xnor2(true_id, false_id),false_id);
    EXPECT_EQ(manager.xnor2(true_id, true_id),true_id);

    EXPECT_EQ(manager.xnor2(a_id, false_id),neg_a_id);
    EXPECT_EQ(manager.xnor2(a_id, true_id),a_id);
    EXPECT_EQ(manager.xnor2(a_id, neg_a_id),false_id);
    EXPECT_EQ(manager.xnor2(a_id, a_id),true_id);

    EXPECT_EQ(manager.xnor2(b_id, false_id),neg_b_id);
    EXPECT_EQ(manager.xnor2(b_id, true_id),b_id);
    EXPECT_EQ(manager.xnor2(b_id, neg_b_id),false_id);
    EXPECT_EQ(manager.xnor2(b_id, b_id),true_id);

    EXPECT_EQ(manager.xnor2(c_id, false_id),neg_c_id);
    EXPECT_EQ(manager.xnor2(c_id, true_id),c_id);
    EXPECT_EQ(manager.xnor2(c_id, neg_c_id),false_id);
    EXPECT_EQ(manager.xnor2(c_id, c_id),true_id);

    EXPECT_EQ(manager.xnor2(d_id, false_id),neg_d_id);
    EXPECT_EQ(manager.xnor2(d_id, true_id),d_id);
    EXPECT_EQ(manager.xnor2(d_id, neg_d_id),false_id);
    EXPECT_EQ(manager.xnor2(d_id, d_id),true_id);

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

/**
 * 'coFactorFalse' function tests
 */
TEST_F(ManagerTest,coFactorFalseTest){
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

/**
 * 'getTopVarName' function tests
 */
TEST_F(ManagerTest,getTopVarNameTest){
    EXPECT_EQ(manager.getTopVarName(false_id),"FALSE");
    EXPECT_EQ(manager.getTopVarName(true_id),"TRUE");
    EXPECT_EQ(manager.getTopVarName(a_id),"a");
    EXPECT_EQ(manager.getTopVarName(b_id),"b");
    EXPECT_EQ(manager.getTopVarName(c_id),"c");
    EXPECT_EQ(manager.getTopVarName(d_id),"d");
    EXPECT_EQ(manager.getTopVarName(a_or_b_id),"a");
    EXPECT_EQ(manager.getTopVarName(c_and_d_id),"c");
    EXPECT_EQ(manager.getTopVarName(f1_id),"a");
    EXPECT_EQ(manager.getTopVarName(f1_id),"a");
}

/**
 * 'findNodes' function tests
 */
TEST_F(ManagerTest,findNodesTest){
    set<BDD_ID> a_or_b_nodes;
    set<BDD_ID> c_and_d_nodes;
    set<BDD_ID> f1_nodes;

    manager.findNodes(a_or_b_id,a_or_b_nodes);
    manager.findNodes(c_and_d_id,c_and_d_nodes);
    manager.findNodes(f1_id,f1_nodes);

    EXPECT_EQ(a_or_b_nodes.size(),4);
    EXPECT_TRUE(a_or_b_nodes.find(false_id)!=a_or_b_nodes.end());
    EXPECT_TRUE(a_or_b_nodes.find(true_id)!=a_or_b_nodes.end());
    EXPECT_TRUE(a_or_b_nodes.find(b_id)!=a_or_b_nodes.end());
    EXPECT_TRUE(a_or_b_nodes.find(a_or_b_id) != a_or_b_nodes.end());

    EXPECT_EQ(c_and_d_nodes.size(),4);
    EXPECT_TRUE(c_and_d_nodes.find(false_id)!=c_and_d_nodes.end());
    EXPECT_TRUE(c_and_d_nodes.find(true_id)!=c_and_d_nodes.end());
    EXPECT_TRUE(c_and_d_nodes.find(d_id)!=c_and_d_nodes.end());
    EXPECT_TRUE(c_and_d_nodes.find(c_and_d_id) != c_and_d_nodes.end());

    EXPECT_EQ(f1_nodes.size(),6);
    EXPECT_TRUE(f1_nodes.find(false_id)!=f1_nodes.end());
    EXPECT_TRUE(f1_nodes.find(true_id)!=f1_nodes.end());
    EXPECT_TRUE(f1_nodes.find(d_id)!=f1_nodes.end());
    EXPECT_TRUE(f1_nodes.find(c_and_d_id) != f1_nodes.end());
    EXPECT_TRUE(f1_nodes.find(manager.and2(b_id,c_and_d_id)) != f1_nodes.end());
    EXPECT_TRUE(f1_nodes.find(f1_id) != f1_nodes.end());
}


/**
 * 'findVars' function tests
 */
TEST_F(ManagerTest,findVarsTest){
    set<BDD_ID> a_or_b_vars;
    set<BDD_ID> c_and_d_vars;
    set<BDD_ID> f1_vars;

    manager.findVars(a_or_b_id,a_or_b_vars);
    manager.findVars(c_and_d_id,c_and_d_vars);
    manager.findVars(f1_id,f1_vars);

    EXPECT_EQ(a_or_b_vars.size(),2);
    EXPECT_TRUE(a_or_b_vars.find(a_id)!=a_or_b_vars.end());
    EXPECT_TRUE(a_or_b_vars.find(b_id) != a_or_b_vars.end());

    EXPECT_EQ(c_and_d_vars.size(),2);
    EXPECT_TRUE(c_and_d_vars.find(c_id)!=c_and_d_vars.end());
    EXPECT_TRUE(c_and_d_vars.find(d_id) != c_and_d_vars.end());

    EXPECT_EQ(f1_vars.size(),4);
    EXPECT_TRUE(f1_vars.find(a_id) != f1_vars.end());
    EXPECT_TRUE(f1_vars.find(b_id) != f1_vars.end());
    EXPECT_TRUE(f1_vars.find(c_id) != f1_vars.end());
    EXPECT_TRUE(f1_vars.find(d_id)!=f1_vars.end());
}
#endif