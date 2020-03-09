#ifndef __OUTREDIRECT_TEST_HPP__
#define __OUTREDIRECT_TEST_HPP__

#include "gtest/gtest.h"
#include <fstream>

#include "../header/token/Connectors/And.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connectors/OutRedirect.hpp"


TEST(OutRedirectOverwrite, BasicTest) {

    string textFile = "text_files/OutRedirectOverwrite.txt";

    vector<string> vct1 = {"echo", "HELLO 123"};
    vector<string> vct2 = {textFile};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);


    Base* test = new OutRedirect(">",cmd1, cmd2);
    EXPECT_TRUE(test->execute());
    EXPECT_EQ(test->stringify(), "echo HELLO 123 > " + textFile);

    std::ifstream fin;
    fin.open(textFile.c_str());
    std::string content( (std::istreambuf_iterator<char>(fin)) ,(std::istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(content,"HELLO 123\n");

    std::ofstream fout;
    fout.open(textFile.c_str(), std::ofstream::out | std::ofstream::trunc);
    fout.close();
}


TEST(OutRedirectAppend, BasicTest) {

    string textFile = "text_files/OutRedirectAppend.txt";


    vector<string> vct1 = {"echo",  "hello"};
    vector<string> vct2 = {textFile};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* test = new OutRedirect(">>",cmd1, cmd2);


    std::ofstream fout;
    fout.open(textFile.c_str(), std::ofstream::out | std::ofstream::trunc);
    fout << "APPEND TO THIS TEXT\n";
    fout.close();


    EXPECT_TRUE(test->execute());
    EXPECT_EQ(test->stringify(), "echo hello >> " + textFile);


    std::ifstream fin;
    fin.open(textFile.c_str());
    std::string content( (std::istreambuf_iterator<char>(fin)) ,(std::istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(content,"APPEND TO THIS TEXT\nhello\n");


}


#endif
