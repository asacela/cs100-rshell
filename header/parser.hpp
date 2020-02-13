#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include<iostream>
#include<vector>
#include<string>
#include<cstring>

#include "../header/token/Base.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Exit.hpp"
#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Or.hpp"
#include "../header/token/Connectors/Semicolon.hpp"

using namespace std;

class Parser{

public:
	Parser(string cmdLine_) : cmdLine(cmdLine_) { }

	void print(){
		if(argList[0] != '\0'){
			cout << argList[0];
		}
		for(int i = 1; argList[i] != '\0'; ++i){
			cout << '\n' << argList[i];
		}
	}

	const char** arguments(){
		return argList;
	}

	Base* parse(){
		// cout << "TEST 1" << endl;

		bool isComment = false;
		for(int i = 0; i < cmdLine.size() && !isComment; ++i){

			char c = cmdLine.at(i);
			string str;

			// If it's a comment
			if(c == '#'){
				isComment = true;
			}

			// If it's a quote
			else if(c == '\"'){
				int end = cmdLine.find('\"',i + 1);

				// Acount for a possible \"
				while(cmdLine.at(end-1) == '\\'){
					cmdLine.erase(cmdLine.begin() + end-1);
					end = cmdLine.find('\"',end);
				}

				string str = cmdLine.substr(i + 1,end - i - 1);
				parsed.push_back(str);

				i = end;
			}

			// KEEP THIS CASE (e.g. echo "hello";)
			// If it's a semicolon
			else if(c == ';'){

				return objectify(";",i+1);
			}

			// If it's not a space
			else if(c != ' '){

				// Look for next appreance of a space
				size_t end = cmdLine.find(' ',i);

				// If no other space found -> have reached the end of cmdLine string
				if(end == string::npos){

					end = cmdLine.size();

					// Create substring
					str = cmdLine.substr(i,end - i);

					// If very last character of sub string is semicolon
					if(str.back() == ';'){
						// Remove semicolon from sub string, push into parsed, make obj
						str.pop_back();
						parsed.push_back(str);
						return objectify(";",end);
					}

					// Else that is the end of the string
					parsed.push_back(str);
					return objectify("list",end);
				}
				else{

					// Create substring
					str = cmdLine.substr(i,end - i);

					// If the char before the space is ';'
					if(str.back() == ';'){

						// Remove semicolon then push into parsed
						str.pop_back();
						parsed.push_back(str);

						return objectify(";", end);
					}
					else if(str == "&&"){
						return objectify("&&",end);
					}
					else if(str == "||"){
						return objectify("||", end);
					}
					// Else it is a regular command -> continue
					parsed.push_back(str);
					i = end - 1;
				}

			}
			else{
				// Ignore white space

			}
		}

		// Base cases: you reach the end of the string (i.e. no more connectors)
		// No arguments received
		if(parsed.size() == 0){
			return nullptr;
		}

		return objectify("list",cmdLine.size());
	}


private:

	Base* objectify(string objType, int startInd){

		to_cstring();

		Base* lhs = new Command(argList);
		Base* objTemp = nullptr;

		// Check if argList is to exit
		if(argList[0] != nullptr){
			if(strcmp(argList[0],"exit") && argList[1] == nullptr){
				// delete lhs;
				lhs = new Exit(argList);
			}
		}

		int newSize = cmdLine.size() - startInd;

		// If we reach the end of the cmdLine
		if(newSize <= 0){
			if(objType == "list"){
				objTemp = lhs;

			}
			else if(objType == ";"){
				if(parsed.size() == 0){
					objTemp = new Semicolon(nullptr, nullptr);

				}
				else{
					objTemp = new Semicolon(lhs, nullptr);

				}

			}
		}
		// Else not finished reading through cmdLine
		else{
			string remainingString = cmdLine.substr(startInd,newSize);
			Parser* parserTemp = new Parser(remainingString);

			if(objType == "&&"){
				objTemp = new And(lhs, parserTemp->parse());

			}
			else if(objType == "||"){
				objTemp = new Or(lhs, parserTemp->parse());

			}
			else if(objType == ";"){
				objTemp = new Semicolon(lhs, parserTemp->parse());

			}
			else if(objType == "list"){
				objTemp = lhs;

			}

		}

		return objTemp;
	}

	void to_cstring(){
		int size = parsed.size();

		argList = new const char*[size+1];
		argList[size] =  nullptr;

		// Populate the argList variable with c_string copies of the parsed
		for(int i = 0; i < size; ++i){
			argList[i] = parsed.at(i).c_str();

		}

	}


	// Private variables
	string cmdLine;
	vector<string> parsed;
	const char** argList;

};

#endif //__PARSER_HPP__
