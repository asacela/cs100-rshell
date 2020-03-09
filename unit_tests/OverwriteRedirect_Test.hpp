#ifndef __OVERWRITEREDIRECT_TEST_HPP__
#define __OVERWRITEREDIRECT_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connectors/OverwriteRedirect.hpp"


TEST(OverwriteRedirect, BasicTest) {

    vector<string> vct1 = {"git",  "status"};
    vector<string> vct2 = {"text_files/new1.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);


    Base* test = new OverwriteRedirect(cmd1, cmd2);
    test->execute();
    EXPECT_EQ(test->stringify(), "echo hello >> text_files/new1.txt");
}


#endif