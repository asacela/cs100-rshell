#ifndef __PARANTHESES_TEST_HPP__
#define __PARANTHESES_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/Or.hpp"


TEST(ParanthesesTest, OrDisplay) {
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"git", "status"};


    Base* open_paran = new Parantheses("(");
    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* closed_paran = new Parantheses(")");

    Base* test = new Or(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "ls -a || git status");
}

#endif // __PARANTHESES_TEST_HPP__
