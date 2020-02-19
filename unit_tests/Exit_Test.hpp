#ifndef __COMMAND_TEST_HPP__
#define __COMMAND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Exit.hpp"


TEST(ExitTest, ExitExecute) {
    Base* test = new Exit({"exit"});
    EXPECT_EQ(test->execute(), true);
}

#endif
