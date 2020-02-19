#ifndef __OR_TEST_HPP__
#define __OR_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/Or.hpp"


TEST(OrTest, OrDisplay) {
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"git", "status"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new Or(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "ls -a || git status");
}
TEST(OrTest, OrExecute) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"git", "status"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new Or(cmd1, cmd2);
  bool rhsResult = false;
  EXPECT_EQ(test->execute(), rhsResult);
}

#endif
