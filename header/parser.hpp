#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include<iostream>
#include<vector>
#include<string>
#include<cstring>

#include "../header/token/Base.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Or.hpp"
#include "../header/token/Connectors/Semicolon.hpp"

using namespace std;
// using namespace boost;

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

		bool isComment = false;
		for(int i = 0; i < cmdLine.size() && !isComment; ++i){

			char c = cmdLine.at(i);

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
					string str = cmdLine.substr(i,end - i);

					// If very last character of sub string is semicolon
					if(str.back() == ';'){
						// Remove semicolon from sub string, push into parsed, make obj
						str.pop_back();
						parsed.push_back(str);
						return objectify(";",end);
					}

					// Else that is the end of the string
					parsed.push_back(str);
					return objectify("arg",end);
				}

				// Else a space is found
				else{
					
					// Create substring
					string str = cmdLine.substr(i,end - i);

					// If the char before the space is ';'
					if(str.back() == ';'){

						// Remove semicolon then push into parsed
						str.pop_back();
						parser.push_back(str);

						return objectify(";", end - 1);
					}
					else if(str == "&&"){
						return objectify("&&",end);
					}
					else if(str == "||"){
						return objectify("||", end);
					}
					// Else it is a regular command -> continue

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

		// Last string received was an argument
		return objectify("arg",cmdLine.size());
	}


private:

	Base* objectify(string objType, int startInd){

		to_cstring();

		Base* lhs = new Command(argList);
		Base* objTemp = nullptr;

		// Check if argList is to exit
		if(argList[0] != nullptr){
			if(argList[0] == "exit" && argList[1] == nullptr){
				delete lhs;
				lhs = new Exit();
			}
		}

		newSize = cmdLine.size() - startInd;

		// If we reach the end of the cmdLine
		if(newSize <= 0){
			if(objType == "arg"){
				objTemp = lhs;

			}
			else if(objType == ";"){
				objTemp = new Semicolon(lhs, nullptr);

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
			else if(objType == "arg"){
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
