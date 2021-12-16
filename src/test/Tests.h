
#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include <string>
#include "Manager.h"
#include <iostream>
using namespace ClassProject;

Manager manager1;

TEST(createVarTest, tableHasValues){
    ASSERT_STREQ(manager1.uniqueTable[0].label.c_str(), "FALSE");
    ASSERT_STREQ(manager1.uniqueTable[1].label.c_str(), "TRUE");
    //for(int i=2; i<manager1.uniqueTable.size(); i++){
      //  ASSERT_STREQ( "NULL","NULL");
     //   ASSERT_EQ(manager1.uniqueTable[i].id,NULL);
   // }
}
//manager1.uniqueTable[i].label.c_str(),

/*TEST(createVarTest,hasUniqueId){

    for(int i=0; i<manager1.uniqueTable.size()-1; i++){
        for(int j=1; j<manager1.uniqueTable.size(); j++){
            EXPECT_NE(manager1.uniqueTable[i].id,manager1.uniqueTable[j].id);
    }
   }
}*/

TEST(trueNodeId, hasIdOne){
    ASSERT_EQ(manager1.uniqueTable[1].id, 1);
}
TEST(falseNodeId,hasIdZero){
    ASSERT_EQ(manager1.uniqueTable[0].id, 0);
}

/**
 * Test for topVar function
 */
//TEST(){
//
//}
#endif
