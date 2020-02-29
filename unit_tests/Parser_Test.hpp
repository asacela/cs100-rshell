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
    Parser* test = new Parser();
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

    EXPECT_EQ(squashed2->stringify(), "(((ls -j || git Status) && echo hello) || ma19d -h)");

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
    EXPECT_FALSE(squashed2->execute());
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
    EXPECT_FALSE(squashed2->execute());
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





/* Tester Class Tests */
TEST(TesterClassTest, BasicExecuteLiteral){
	Base* test = new Tester({"test","-e","names.txt"});
  testing::internal::CaptureStdout();
  test->execute();
  std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(TRUE)\n");
  	EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, BasicStringifyLiteral){
        Base* test = new Tester({"test","-e","names.txt"});
        EXPECT_EQ(test->stringify(),"test -e names.txt");
}
TEST(TesterClassTest, BasicExecuteSymbolic){
        Base* test = new Tester({"[","-e","names.txt","]"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(TRUE)\n");
        EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, BasicStringifySymbolic){
        Base* test = new Tester({"[","-e","names.txt", "]"});
        EXPECT_EQ(test->stringify(),"test -e names.txt");
}

TEST(TesterClassTest, StdFlagExecuteLiteral){
        Base* test = new Tester({"test","names.txt"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(TRUE)\n");
          EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, StdFlagStringifyLiteral){
        Base* test = new Tester({"test","names.txt"});
        EXPECT_EQ(test->stringify(),"test -e names.txt");
}
TEST(TesterClassTest, StdFlagExecuteSymbolic){
        Base* test = new Tester({"[","names.txt","]"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(TRUE)\n");
          EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, StdFlagStringifySymbolic){
        Base* test = new Tester({"[","names.txt", "]"});
        EXPECT_EQ(test->stringify(),"test -e names.txt");
}

TEST(TesterClassTest, FFlagExecuteLiteral){
        Base* test = new Tester({"test","-f","names.txt"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(TRUE)\n");
          EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, FFlagStringifyLiteral){
        Base* test = new Tester({"test","-f","names.txt"});
        EXPECT_EQ(test->stringify(),"test -f names.txt");
}
TEST(TesterClassTest, FFlagExecuteSymbolic){
        Base* test = new Tester({"[","-f","names.txt","]"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(TRUE)\n");
          EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, FFlagStringifySymbolic){
        Base* test = new Tester({"[","-f","names.txt", "]"});
        EXPECT_EQ(test->stringify(),"test -f names.txt");
}

TEST(TesterClassTest, DFlagExecuteLiteral){
        Base* test = new Tester({"test","-d","names.txt"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(FALSE)\n");
          EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, DFlagStringifyLiteral){
        Base* test = new Tester({"test","-d","names.txt"});
        EXPECT_EQ(test->stringify(),"test -d names.txt");
}
TEST(TesterClassTest, DFlagExecuteSymbolic){
        Base* test = new Tester({"[","-d","names.txt","]"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "(FALSE)\n");
          EXPECT_TRUE(test->execute());
}
TEST(TesterClassTest, DFlagStringifySymbolic){
        Base* test = new Tester({"[","-d","names.txt", "]"});
        EXPECT_EQ(test->stringify(),"test -d names.txt");
}

TEST(TesterClassTest, EmptyExecuteLiteral){
        Base* test = new Tester({"test"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "");
          EXPECT_FALSE(test->execute());
}
TEST(TesterClassTest, EmptyStringifyLiteral){
        Base* test = new Tester({"test"});
        EXPECT_EQ(test->stringify(),"test");
}
TEST(TesterClassTest, EmptyExecuteSymbolic){
        Base* test = new Tester({"[","]"});
        testing::internal::CaptureStdout();
        test->execute();
        std::string output = testing::internal::GetCapturedStdout();
          EXPECT_EQ(output, "");
          EXPECT_FALSE(test->execute());
}
TEST(TesterClassTest, EmptyStringifySymbolic){
        Base* test = new Tester({"[","]"});
        EXPECT_EQ(test->stringify(),"test");
}





/* Precedence Tests */
TEST(PrecedenceTest, AndCommandDisplay){

	Parser* parserObj = new Parser("(ls -a && git status)");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "(ls -a && git status)");
}
TEST(PrecedenceTest, AndCommandExecute){

	Parser* parserObj = new Parser("(ls -a && git status)");
  Base* test = parserObj->getSquashed();
    EXPECT_TRUE(test->execute());
}

TEST(PrecedenceTest, OrCommandDisplay){

	Parser* parserObj = new Parser("(ls -a || git status)");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "(ls -a || git status)");
}
TEST(PrecedenceTest, OrCommandExecute){

	Parser* parserObj = new Parser("(ls -a || git status)");
  Base* test = parserObj->getSquashed();
    EXPECT_TRUE(test->execute());
}

TEST(PrecedenceTest, SemicolonDisplay_1){

	Parser* parserObj = new Parser("(ls -j; git status)");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "ls -j; git status");
}
TEST(PrecedenceTest, SemicolonExecute_1){

	Parser* parserObj = new Parser("(ls -j; git status)");
  Base* test = parserObj->getSquashed();
    EXPECT_TRUE(test->execute());
}
TEST(PrecedenceTest, SemicolonDisplay_2){

	Parser* parserObj = new Parser("(ls -j; )");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "ls -j;");
}
TEST(PrecedenceTest, SemicolonExecute_2){

	Parser* parserObj = new Parser("(ls -j; )");
  Base* test = parserObj->getSquashed();
    EXPECT_FALSE(test->execute());
}

TEST(PrecedenceTest, MultiCommandDisplay_1){

	Parser* parserObj = new Parser("(echo A && echo B) || (echo C && echo D)");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "((echo A && echo B) || (echo C && echo D))");
}
TEST(PrecedenceTest, MultiCommandExecute_1){

	Parser* parserObj = new Parser("(echo A && echo B) || (echo C && echo D)");
  Base* test = parserObj->getSquashed();
    EXPECT_TRUE(test->execute());
}

TEST(PrecedenceTest, MultiCommandDisplay_2){

	Parser* parserObj = new Parser("(echo A || echo B) && (echo C || echo D)");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "((echo A || echo B) && (echo C || echo D))");
}
TEST(PrecedenceTest, MultiCommandExecute_2){

	Parser* parserObj = new Parser("(echo A || echo B) && (echo C || echo D)");
  Base* test = parserObj->getSquashed();
    EXPECT_TRUE(test->execute());
}

TEST(PrecedenceTest, MultiCommandDisplay_3){

	Parser* parserObj = new Parser("(echo A && ls -j) || (ls -z && echo D)");
  Base* test = parserObj->getSquashed();
    EXPECT_EQ(test->stringify(), "((echo A && ls -j) || (ls -z && echo D))");
}
TEST(PrecedenceTest, MultiCommandExecute_3){

	Parser* parserObj = new Parser("(echo A && ls -j) || (ls -z && echo D)");
  Base* test = parserObj->getSquashed();
    EXPECT_FALSE(test->execute());
}







  /* --DANGEROUS-- */
  /* Uncomment at your own risk */
// TEST(StressTest, BreakDisplay_NoPrecedence){
//
// 	Parser* parserObj = new Parser("");
//   Base* test = parserObj->getSquashed();
//     EXPECT_EQ(test->stringify(), " ; echo A && echo B && ls -j || ls -z && echo D;  echo no && echo bye;  echo failed ; echo bye \"  #not a comment \" || echo no; bleh   # echo comented this thing ;");
// }
// TEST(StressTest, BreakDisplay_Precedence){
//
// 	Parser* parserObj = new Parser("");
//   Base* test = parserObj->getSquashed();
//     EXPECT_EQ(test->stringify(), "(( ; echo A && (echo B && ls -j) || (ls -z && echo D; )) || echo no && echo bye; ) || echo failed ; (echo bye \"  #not a comment \" || (echo no; bleh  )) # echo comented this thing ;");
// }

// TEST(PrecedenceTest, LongMultiCommandDisplay_1){
//
// 	Parser* parserObj = new Parser("( ; echo A && (echo B && ls -j) || (ls -z && echo D; )) || echo no && echo bye;");
//   Base* test = parserObj->getSquashed();
//     EXPECT_EQ(test->stringify(), "(((; (echo A && (echo B && ls -j)) || (ls -z && echo D;)) || echo no) && echo bye);");
// }
// TEST(PrecedenceTest, LongMultiCommandExecute_1){
//
//   Parser* parserObj = new Parser("( ; echo A && (echo B && ls -j) || (ls -z && echo D; )) || echo no && echo bye;");
//   Base* test = parserObj->getSquashed();
//     EXPECT_FALSE(test->execute());
// }

#endif
