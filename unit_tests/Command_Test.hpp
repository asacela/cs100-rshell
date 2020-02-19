#ifndef __COMMAND_TEST_HPP__
#define __COMMAND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Command.hpp"


TEST(CommandTest, CommandDisplay) {
    Base* test = new Command("ls -a");
    EXPECT_EQ(test->display(), "ls -a");
}
TEST(CommandTest, CommandExecute) {
    Base* test = new Command("ls -a");
    EXPECT_EQ(test->execute(), true);
}

#endif 
