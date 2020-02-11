#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"


TEST(AndTest, AndDisplay) {
    And* test = new And("ls -a", "git status");
    EXPECT_EQ(test->display(), "ls -a");
}
TEST(AndTest, AndExecute) {
    And* test = new And("ls -a", "git status");
    EXPECT_EQ(test->execute(), true);
}

#endif __AND_TEST_HPP__