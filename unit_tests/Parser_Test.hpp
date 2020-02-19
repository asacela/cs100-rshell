#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/Parser.hpp"
#include<vector>

using namespace testing;


/* Squash Tests*/
TEST(SquashTest, SquashSmallInput){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -a && git status");
    Base* cmd1 = new Command({"ls", "-a"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And(cmd1, cmd2);


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(squashed1);
    Base* squashed2 = test->testSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_EQ(squashed1->stringify(), squashed2->stringify());
}
TEST(SquashTest, SquashExecuteLongCommand){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -j");
    Base* cmd1 = new Command({"ls", "-j"});
    Base* cmd2 = new Or();
    Base* cmd3 = new Command({"git", "Status"});
    Base* cmd4 = new And();
    Base* cmd5 = new Command({"echo", "hello"});
    Base* cmd6 = new Or();
    Base* cmd7 = new Command({"ma19d", "-h"});



    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    baseList.push_back(cmd2);
    baseList.push_back(cmd3);
    baseList.push_back(cmd4);
    baseList.push_back(cmd5);
    baseList.push_back(cmd6);
    baseList.push_back(cmd7);

    Base* squashed2 = test->testSquashed(baseList);

    /* compares resulting objects' strings with stringify */

    EXPECT_EQ(squashed2->stringify(), "ls -j || git Status && echo hello || ma19d -h");
    //EXPECT_TRUE(squashed2->execute() == false);
}
TEST(SquashTest, SquashExecuteInvalidCommand){


	/* objects for testing squash, stringify */

    Parser* test = new Parser();
    Base* cmd1 = new Command({"gert", "flop"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And();


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    baseList.push_back(squashed1);
    baseList.push_back(cmd2);
    Base* squashed2 = test->testSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute());
}
TEST(SquashTest, SquashExecuteAndConnector){


	/* objects for testing squash, stringify */

    Parser* test = new Parser("ls -j && git status");
    Base* cmd1 = new Command({"ls", "-j"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And();


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    baseList.push_back(squashed1);
    baseList.push_back(cmd2);

    Base* squashed2 = test->testSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute());
}
TEST(SquashTest, SquashExecuteOrConnector){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -j || git status");
    Base* cmd1 = new Command({"ls", "-j"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new Or();


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    baseList.push_back(squashed1);
    baseList.push_back(cmd2);
    Base* squashed2 = test->testSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}
TEST(SquashTest, SquashExecuteSemicolonConnector){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("");
    Base* cmd1 = new Command({"ls", "-a"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* connector = new Semicolon();


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    baseList.push_back(connector);
    baseList.push_back(cmd2);

    Base* squashed2 = test->testSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}


/* Parse Tests*/
TEST(ParseTest, ParseAndShortCommand){

	Parser* test = new Parser("ls -a && git status");
    EXPECT_EQ(test->test().size(), 3);
}
TEST(ParseTest, ParseOrShortCommand){

	Parser* test = new Parser("ls -a || git status");
    EXPECT_EQ(test->test().size(), 3);
}
TEST(ParseTest, ParseSemicolonShortCommand){

	Parser* test = new Parser("ls -a; git status");
    EXPECT_EQ(test->test().size(), 3);
}
TEST(ParseTest, ParseLongCommand){

	Parser* test = new Parser("ls -a && git status || echo hello; git status; git status || echo \"bye\"");
    EXPECT_EQ(test->test().size(), 11);
}
TEST(ParseTest, ParseLongBrokenCommand){

	Parser* test = new Parser("ls123 -a && gi1234t status || echo h1234ello; git stat1234us; git s1234tatus || e1234cho \"bye\"");
    EXPECT_EQ(test->test().size(), 11);
}
TEST(ParseTest, ParseExtraLongCommand){

	Parser* test = new Parser("ls -a && git status || echo hello; git status; git status || echo \"bye\"; git status || echo hello; ; git status || echo hello;");
    EXPECT_EQ(test->test().size(), 21);
}

#endif
