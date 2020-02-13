#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/Parser.hpp"


TEST(SquashTest, SquashSmallInput){

    Parser* test = new Parser("ls -a && git status");
    Base* cmd1 = new Command("ls -a");
    Base* cmd2 = new Command("git status");
    Base* squashed = new Connector(cmd1, cmd2);
    EXPECT_EQ(test->squash(), squashed);
}

#endif __PARSER_TEST_HPP__
