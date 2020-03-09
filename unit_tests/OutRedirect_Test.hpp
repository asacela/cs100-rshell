#ifndef __OUTREDIRECT_TEST_HPP__
#define __OUTREDIRECT_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connectors/OutRedirect.hpp"


TEST(OutRedirectOverwrite, BasicTest) {

    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"text_files/OutRedirect_BasicTest.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);


    Base* test = new OutRedirect(">",cmd1, cmd2);
    test->execute();
    EXPECT_EQ(test->stringify(), "ls -a > text_files/OutRedirect_BasicTest.txt");
}


TEST(OutRedirectAppend, BasicTest) {

    vector<string> vct1 = {"echo",  "hello"};
    vector<string> vct2 = {"text_files/OutRedirectAppend_BasicTest.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);


    Base* test = new OutRedirect(">>",cmd1, cmd2);
    test->execute();
    EXPECT_EQ(test->stringify(), "echo hello >> text_files/OutRedirectAppend_BasicTest.txt");
}


#endif
