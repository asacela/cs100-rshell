#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/Parser.hpp"
#include<vector>

using namespace testing;


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
    Base* squashed2 = test->getSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_EQ(squashed1->stringify(), squashed2->stringify());
}
TEST(SquashTest, SquashExecuteCommandBadArg){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -j");
    Base* cmd1 = new Command({"ls", "-j"});


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    Base* squashed2 = test->getSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}
TEST(SquashTest, SquashExecuteInvalidCommand){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("gert12 floofy && git status");
    Base* cmd1 = new Command({"gert12", "floofy"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And(cmd1, cmd2);


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(squashed1);
    Base* squashed2 = test->getSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}
TEST(SquashTest, SquashExecuteAndConnector){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -a && git status");
    Base* cmd1 = new Command({"ls", "-j"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And(cmd1, cmd2);


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(squashed1);
    Base* squashed2 = test->getSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}
TEST(SquashTest, SquashExecuteOrConnector){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -a || git status");
    Base* cmd1 = new Command({"ls", "-j"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And(cmd1, cmd2);


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(squashed1);
    Base* squashed2 = test->getSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}
TEST(SquashTest, SquashExecuteSemicolonConnector){


	/* objects for testing squash, stringify */
    Parser* test = new Parser("ls -a; git status");
    Base* cmd1 = new Command({"ls", "-j"});
    Base* cmd2 = new Command({"git", "status"});


    /* set up first base* for comparison */
    Base* squashed1 = new And(cmd1, cmd2);


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(squashed1);
    Base* squashed2 = test->getSquashed(baseList);

    /* compares resulting objects' strings with stringify */
    EXPECT_TRUE(squashed2->execute() == true);
}







#endif
