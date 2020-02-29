#ifndef __COMMAND_TEST_HPP__
#define __COMMAND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Command.hpp"


TEST(CommandTest, CommandDisplay) {
    Base* test = new Command({"ls","-a"});
    EXPECT_EQ(test->stringify(), "ls -a");
}
TEST(CommandTest, CommandExecute) {
    Base* test = new Command({"ls","-a"});
    EXPECT_TRUE(test->execute());
}

TEST(CommandTest, InvalidCommandDisplay) {
    Base* test = new Command({"ls","-j"});
    EXPECT_EQ(test->stringify(), "ls -j");
}
TEST(CommandTest, InvalidCommandExecute) {
    Base* test = new Command({"ls","-j"});
    EXPECT_FALSE(test->execute());
}


#endif
