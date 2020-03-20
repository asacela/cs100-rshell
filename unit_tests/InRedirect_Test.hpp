#ifndef __INREDIRECT_TEST_HPP__
#define __INREDIRECT_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connectors/InRedirect.hpp"


TEST(InRedirect, BasicTest) {

    vector<string> vct1 = {"cat"};
    vector<string> vct2 = {"text_files/InRedirect.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* test = new InRedirect(cmd1, cmd2);

    testing::internal::CaptureStdout();
    EXPECT_TRUE(test->execute());

    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Greetings from file!\n");

    EXPECT_EQ(test->stringify(), "cat < text_files/InRedirect.txt");
}

TEST(InRedirect, MultiTest) {

    vector<string> vct1 = {"cat"};
    vector<string> vct2 = {"text_files/InRedirect.txt"};
    vector<string> vct3 = {"text_files/static.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* cmd3 = new Command(vct3);
    Base* test = new InRedirect(cmd1, cmd2);
    Base* test2 = new InRedirect(test, cmd3);

    testing::internal::CaptureStdout();
    EXPECT_TRUE(test2->execute());

    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Greetings from file!\nDon't change\n");

    EXPECT_EQ(test2->stringify(), "cat < text_files/InRedirect.txt < text_files/static.txt");
}


#endif
