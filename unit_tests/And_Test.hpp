#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Command.hpp"


TEST(AndTest, AndDisplay) {
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"git", "status"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new And(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "ls -a && git status");
}
TEST(AndTest, AndExecute) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"git", "status"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new And(cmd1, cmd2);
  bool rhsResult = true;
  EXPECT_EQ(test->execute(), rhsResult);
}

#endif
