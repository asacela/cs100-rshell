#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/Parser.hpp"


TEST(CommandTest, ParserPrint_Empty) {
    Parser* test = new Parser("");
    EXPECT_EQ(test->print(), "");
}
TEST(CommandTest, ParserPrint_Spaces) {
    Parser* test = new Parser("   ");
    EXPECT_EQ(test->print(), "");
}
TEST(CommandTest, ParserPrint_AlphaNumeric) {
    Parser* test = new Parser("Hello12345");
    EXPECT_EQ(test->print(), "Hello12345");
}
TEST(CommandTest, ParserPrint_Multiple) {
    Parser* test = new Parser("H3llo w0rld!");
    EXPECT_EQ(test->print(), "H3llo\nw0rld!");
}
TEST(CommandTest, ParserPrint_Quotes) {
    Parser* test = new Parser("\"Quote this\"");
    EXPECT_EQ(test->print(), "Quote this");
}
TEST(CommandTest, ParserPrint_InnerQuotes) {
    Parser* test = new Parser("\"I \\\"like\\\"\" you");
    EXPECT_EQ(test->print(), "I \"like\"\nyou");
}
TEST(CommandTest, ParserPrint_Comment) {
    Parser* list = new Parser("This is #a comment");
    EXPECT_EQ(test->execute(), "This is");
}
// TEST(CommandTest, ParserPrint_And) {
//     Parser* list = new Parser("This && that");
//     EXPECT_EQ(test->execute(), "This\n&&\nthat");
// }
// TEST(CommandTest, ParserPrint_Or) {
//   Parser* list = new Parser("This || that");
//   EXPECT_EQ(test->execute(), "This\n||\nthat");
// }
// TEST(CommandTest, ParserPrint_Semicolon) {
//     Parser* list = new Parser("How; about; this;");
//     EXPECT_EQ(test->execute(), "How\nabout\nthis");
}

#endif
