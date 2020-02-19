#ifndef __SEMICOLON_TEST_HPP__
#define __SEMICOLON_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/Semicolon.hpp"
#include "../header/token/Command.hpp"

TEST(SemicolonTest, SDisplay) {
    Base* test = new Semicolon();

    EXPECT_EQ(test->stringify(), ";");
}
TEST(SemicolonTest, SExecute) {
    Base* test = new Semicolon();

    EXPECT_TRUE(test->execute());
}

TEST(SemicolonTest, CSDisplay) {
    vector<string> vct1 = {"echo", "hello"};

    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(cmd1, nullptr);

    EXPECT_EQ(test->stringify(), "echo hello;");
}
TEST(SemicolonTest, CSExecute) {
    vector<string> vct1 = {"echo",  "hello"};

    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(cmd1, nullptr);

    EXPECT_TRUE(test->execute());
}

TEST(SemicolonTest, CSCDisplay) {
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"echo", "hello"};

    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* test = new Semicolon(cmd1, cmd2);

    EXPECT_EQ(test->stringify(), "ls -a; echo hello");
}
TEST(SemicolonTest, CSCExecute) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"echo", "hello"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);
  Base* test = new Semicolon(cmd1, cmd2);

  EXPECT_TRUE(test->execute());
}

TEST(SemicolonTest, CSCSDisplay) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"echo", "hello"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);
  Base* connector = new Semicolon(cmd1, cmd2);
  Base* test = new Semicolon(connector, nullptr);

    EXPECT_EQ(test->stringify(), "ls -a; echo hello;");
}
TEST(SemicolonTest, CSCSExecute) {
  vector<string> vct1 = {"ls",  "-a"};
  vector<string> vct2 = {"echo", "hello"};

  Base* cmd1 = new Command(vct1);
  Base* cmd2 = new Command(vct2);
  Base* connector = new Semicolon(cmd1, cmd2);
  Base* test = new Semicolon(connector, nullptr);

  EXPECT_TRUE(test->execute());
}

TEST(SemicolonTest, ICSDisplay) {
    vector<string> vct1 = {"ls",  "-j"};
    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(cmd1, nullptr);

    EXPECT_EQ(test->stringify(), "ls -j;");
}
TEST(SemicolonTest, ICSExecute) {
    vector<string> vct1 = {"ls",  "-j"};
    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(cmd1, nullptr);

    EXPECT_TRUE(test->execute());
}

TEST(SemicolonTest, ICSICDisplay) {
    vector<string> vct1 = {"ls",  "-j"};
    vector<string> vct2 = {"gert",  "flop"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new Semicolon(cmd1, cmd2);

    EXPECT_EQ(test->stringify(), "ls -j; gert flop");
}
TEST(SemicolonTest, ICSICExecute) {
    vector<string> vct1 = {"ls",  "-j"};
    vector<string> vct2 = {"gert",  "flop"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);

    Base* test = new Semicolon(cmd1, cmd2);

    EXPECT_FALSE(test->execute());
}

TEST(SemicolonTest, SICDisplay) {
    vector<string> vct1 = {"ls",  "-j"};
    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(nullptr, cmd1);

    EXPECT_EQ(test->stringify(), "; ls -j");
}
TEST(SemicolonTest, SICExecute) {
    vector<string> vct1 = {"ls",  "-j"};
    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(nullptr, cmd1);

    EXPECT_FALSE(test->execute());
}

TEST(SemicolonTest, SCDisplay) {
    vector<string> vct1 = {"ls"};
    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(nullptr, cmd1);

    EXPECT_EQ(test->stringify(), "; ls");
}
TEST(SemicolonTest, SCExecute) {
    vector<string> vct1 = {"ls"};
    Base* cmd1 = new Command(vct1);
    Base* test = new Semicolon(nullptr, cmd1);

    EXPECT_TRUE(test->execute());
}

TEST(SemicolonTest, SCSDisplay) {
    vector<string> vct1 = {"ls",  "-a"};

    Base* cmd1 = new Command(vct1);
    Base* connector1 = new Semicolon(nullptr, cmd1);
    Base* connector2 = new Semicolon(connector1, nullptr);


    EXPECT_EQ(connector2->stringify(), "; ls -a;");
}
TEST(SemicolonTest, SCSExecute) {
    vector<string> vct1 = {"ls",  "-a"};

    Base* cmd1 = new Command(vct1);
    Base* connector1 = new Semicolon(nullptr, cmd1);
    Base* connector2 = new Semicolon(connector1, nullptr);


    EXPECT_TRUE(connector2->execute());
}

#endif

