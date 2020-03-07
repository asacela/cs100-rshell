#ifndef __IN_REDIRECT_TEST_HPP__
#define __IN_REDIRECT_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Command.hpp"
#include "../header/token/Connectors/InRedirect.hpp"


TEST(InRedirect, BasicTest) {
    vector<string> vct1 = {"echo",  "hello"};
    vector<string> vct2 = {"/text_files/new.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);


    Base* test = new InRedirect(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "ls -a < git status");
}


#endif
