#ifndef __OUTREDIRECT_TEST_HPP__
#define __OUTREDIRECT_TEST_HPP__

#include "gtest/gtest.h"
#include <fstream>
#include <string>

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


    /* Check textFile before overwriting */
    // Write into textFile
    ofstream fout;
    fout.open(textFile, ofstream::out | ofstream::trunc);
    fout << "OVERWRITE THIS TEXT\n";
    fout.close();
    // Check textFile
    ifstream fin;
    fin.open(textFile);
    string contentBefore( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentBefore,"OVERWRITE THIS TEXT\n");

    /* Overwrite textFile */
    EXPECT_TRUE(test->execute());
    EXPECT_EQ(test->stringify(), "echo HELLO 123 > " + textFile);

    /* Check textFile after overwriting */
    fin.open(textFile);
    string contentAfter( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
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
    ofstream fout;
    fout.open(textFile, ofstream::out | ofstream::trunc);
    fout << "APPEND TO THIS TEXT\n";
    fout.close();
    // Check textFile
    ifstream fin;
    fin.open(textFile);
    string contentBefore( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentBefore,"APPEND TO THIS TEXT\n");

    /* Append to textFile */
    EXPECT_TRUE(test->execute());
    EXPECT_EQ(test->stringify(), "echo hello >> " + textFile);

    /* Check textFile after appending */
    fin.open(textFile);
    string contentAfter( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentAfter,"APPEND TO THIS TEXT\nhello\n");


}

TEST(OutRedirectAppend, MultiTest) {

    string textFile = "text_files/OutRedirectAppend.txt";
    string textFile2 = "text_files/temp.txt";


    vector<string> vct1 = {"echo",  "hello"};
    vector<string> vct2 = {textFile};
    vector<string> vct3 = {textFile2};


    Base* cmd1 = new Command(vct1);
    Base* cmd2 = new Command(vct2);
    Base* cmd3 = new Command(vct3);
    Base* test = new OutRedirect(">>",cmd1, cmd2);
    Base* test2 = new OutRedirect(">>",test,cmd3);


    /* Check textFilefile before appending */
    // Write into textFile
    ofstream fout;
    fout.open(textFile, ofstream::out | ofstream::trunc);
    fout << "APPEND TO THIS TEXT\n";
    fout.close();
    // Check textFile
    ifstream fin;
    fin.open(textFile);
    string contentBefore( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentBefore,"APPEND TO THIS TEXT\n");

    // Write into textFile2
    fout.open(textFile2, ofstream::out | ofstream::trunc);
    fout << "Hello world!\n";
    fout.close();

    /* Append to textFile */
    EXPECT_TRUE(test2->execute());
    EXPECT_EQ(test2->stringify(), "echo hello >> " + textFile + " >> " + textFile2);

    /* Check textFile after appending */
    fin.open(textFile);
    string contentAfter( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentAfter,"APPEND TO THIS TEXT\nhello\n");

    /* Check textFile2 after appending */
    fin.open(textFile2);
    string contentAfter2( (istreambuf_iterator<char>(fin)) ,(istreambuf_iterator<char>()));
    fin.close();
    EXPECT_EQ(contentAfter2,"Hello world!\nhello\n");
}


#endif
