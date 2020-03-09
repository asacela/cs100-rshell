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


    /* Check textFilefile before overwriting */
    // Write into textFile
    std::ofstream fout;
    fout.open(textFile.c_str(), std::ofstream::out | std::ofstream::trunc);
    fout << "OVERWRITE THIS TEXT\n";
    fout.close();
    // Check textFile
    std::ifstream fin;
    fin.open(textFile.c_str());
    std::string contentBefore( (std::istreambuf_iterator<char>(fin)) ,(std::istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentBefore,"OVERWRITE THIS TEXT\n");

    /* Overwrite textFile */
    EXPECT_TRUE(test->execute());
    EXPECT_EQ(test->stringify(), "echo HELLO 123 > " + textFile);

    /* Check textFilefile after overwriting */
    fin.open(textFile.c_str());
    std::string contentAfter( (std::istreambuf_iterator<char>(fin)) ,(std::istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentAfter,"HELLO 123\n");

}


TEST(OutRedirectAppend, BasicTest) {

    string textFile = "text_files/OutRedirectAppend.txt";


    vector<string> vct1 = {"echo",  "hello"};
    vector<string> vct2 = {textFile};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* test = new OutRedirect(">>",cmd1, cmd2);


    /* Check textFilefile before appending */
    // Write into textFile
    std::ofstream fout;
    fout.open(textFile.c_str(), std::ofstream::out | std::ofstream::trunc);
    fout << "APPEND TO THIS TEXT\n";
    fout.close();
    // Check textFile
    std::ifstream fin;
    fin.open(textFile.c_str());
    std::string contentBefore( (std::istreambuf_iterator<char>(fin)) ,(std::istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentBefore,"APPEND TO THIS TEXT\n");


    /* Append to textFile */
    EXPECT_TRUE(test->execute());
    EXPECT_EQ(test->stringify(), "echo hello >> " + textFile);

    /* Check textFile after appending */
    fin.open(textFile.c_str());
    std::string contentAfter( (std::istreambuf_iterator<char>(fin)) ,(std::istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentAfter,"APPEND TO THIS TEXT\nhello\n");


}


#endif
