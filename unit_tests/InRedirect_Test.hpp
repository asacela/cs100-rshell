#ifndef __INREDIRECT_TEST_HPP__
#define __INREDIRECT_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connectors/InRedirect.hpp"


TEST(InRedirect, BasicTest) {
	
    vector<string> vct1 = {"ls",  "-a"};
    vector<string> vct2 = {"text_files/echo.txt"};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);


    Base* test = new InRedirect(cmd1, cmd2);
    test->execute();
    EXPECT_EQ(test->stringify(), "echo hello < text_files/new.txt");
}


#endif
