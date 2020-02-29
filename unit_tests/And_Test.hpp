#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Command.hpp"


TEST(AndTest, CACDisplay) {
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"git", "status"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new And(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "(ls -a && git status)");
}
TEST(AndTest, CACExecute) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"git", "status"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new And(cmd1, cmd2);
  EXPECT_TRUE(test->execute());
}

TEST(AndTest, ICACDisplay) {
    vector<string> vct1 = {"ls",  "-j"};
    vector<string> vct2 = {"echo", "hello"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new And(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "(ls -j && echo hello)");
}
TEST(AndTest, ICACExecute) {
  vector<string> vct1 = {"ls",  "-j"};
  vector<string> vct2 = {"echo", "hello"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new And(cmd1, cmd2);
  EXPECT_FALSE(test->execute());
}

TEST(AndTest, CAICDisplay) {
    vector<string> vct2 = {"ls",  "-j"};
    vector<string> vct1 = {"echo", "hello"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new And(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "(echo hello && ls -j)");
}
TEST(AndTest, CAICExecute) {
  vector<string> vct2 = {"ls",  "-j"};
  vector<string> vct1 = {"echo", "hello"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new And(cmd1, cmd2);
  EXPECT_FALSE(test->execute());
}

TEST(AndTest, ICAICDisplay) {
    vector<string> vct1 = {"ls",  "-j"};
    vector<string> vct2 = {"gert", "flop"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new And(cmd1, cmd2);
    EXPECT_EQ(test->stringify(), "(ls -j && gert flop)");
}
TEST(AndTest, ICAICExecute) {
  vector<string> vct1 = {"ls",  "-j"};
  vector<string> vct2 = {"gert", "flop"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);

  Base* test = new And(cmd1, cmd2);
  EXPECT_FALSE(test->execute());
}

#endif
