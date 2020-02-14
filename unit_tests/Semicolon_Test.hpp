#ifndef __SEMICOLON_TEST_HPP__
#define __SEMICOLON_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/Semicolon.hpp"
#include "../header/token/Connectors/Command.hpp"


TEST(OrTest, OrDisplay) {
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"git", "status"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new Semicolon(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "ls -a; git status");
}
TEST(OrTest, OrExecute) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"git", "status"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new Semicolon(cmd1, cmd2);
  bool rhsResult = true;
  EXPECT_EQ(test->execute(), rhsResult);
}

#endif