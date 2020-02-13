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

	Base* parse(){

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
						if(str != ""){
							parsed.push_back(str);
						}
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
						if(str != ""){
							parsed.push_back(str);
						}
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
		}

		// Base cases: you reach the end of the string (i.e. no more connectors)
		// No arguments received
		if(parsed.size() == 0){
			return nullptr;
		}

		return objectify("list",cmdLine.size());
	}

	Base* getSquashed(vector<Base*> objectList){

		Base* squashed = squash(objectList);
		return squashed;
	}


private:

	Base* objectify(string objType, int startInd){
		Base* lhs = new Command(parsed);
		Base* objTemp = nullptr;
		Parser* parserTemp = nullptr;

		// Check if parsed is to exit
		if(parsed.size() == 1){
			if(parsed.at(0) == "exit"){
				// delete lhs;
				lhs = new Exit(parsed);
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
					// delete lhs;
					lhs = nullptr;
					objTemp = new Semicolon(nullptr, nullptr);

				}
				else{
					objTemp = new Semicolon(nullptr, nullptr);

				}

			}
		}
		// Else not finished reading through cmdLine
		else{
			string remainingString = cmdLine.substr(startInd,newSize);
			parserTemp = new Parser(remainingString);

			if(objType == "&&"){
				objTemp = new And();

			}
			else if(objType == "||"){
				objTemp = new Or();

			}
			else if(objType == ";"){
				objTemp = new Semicolon();

			}
			else if(objType == "list"){
				objTemp = lhs;

			}

		}

		if(lhs != nullptr){
			baseList.push_back(lhs);

			if(objTemp != lhs){
				baseList.push_back(objTemp);
			}
		}
		else if(objTemp != nullptr){
			baseList.push_back(objTemp);
		}

		parserTemp->parse();

		return objTemp;
	}

	Base* squash(vector<Base*> objectList){

		
		Base* squashed;
		
		for(int i = 0; i < objectList.size(); ++i){

			try{

				if(i == 0){

					squashed = objectList.at(i);
				}
				else if(i == 1){

					if(objectList.at(i)->getID() == "&&"){
						
						objectList.at(i)->set_lhs(objectList.at(i - 1));
						if(objectList.at(i + 1) != nullptr){

							objectList.at(i)->set_rhs(objectList.at(i + 1));
						}
						

						squashed = objectList.at(i);
					}
					
					else if(objectList.at(i)->getID() == "||"){

						objectList.at(i)->set_lhs(objectList.at(i - 1));
						if(objectList.at(i + 1) != nullptr){

							objectList.at(i)->set_rhs(objectList.at(i + 1));
						}

						squashed = objectList.at(i);
					}

					else if(objectList.at(i)->getID() == ";"){

						objectList.at(i)->set_lhs(objectList.at(i - 1));
						if(objectList.at(i + 1) != nullptr){

							objectList.at(i)->set_rhs(objectList.at(i + 1));
						}

						squashed = objectList.at(i);
					}			
				}
				else if(objectList.at(i)->getID() == "&&"){

					objectList.at(i)->set_lhs(squashed);
					if(objectList.at(i + 1) != nullptr){

							objectList.at(i)->set_rhs(objectList.at(i + 1));
					}

					squashed = objectList.at(i);		
				}
				
				else if(objectList.at(i)->getID() == "||"){

					objectList.at(i)->set_lhs(squashed);
					if(objectList.at(i + 1) != nullptr){

							objectList.at(i)->set_rhs(objectList.at(i + 1));
					}

					squashed = objectList.at(i);
				}
				else if(objectList.at(i)->getID() == ";"){

					objectList.at(i)->set_lhs(squashed);
					if(objectList.at(i + 1) != nullptr){

							objectList.at(i)->set_rhs(objectList.at(i + 1));
					}

					squashed = objectList.at(i);
				} 
			}
			catch(const std::out_of_range& e){

				cout << "out_of_range error:" << e.what() << endl;
				exit(1);
			}

		}	
		return squashed;
	}

	// Private variables
	string cmdLine;
	vector<string> parsed;
	vector<Base*> baseList;
	// const char** argList;

	const string andOperator = "&&";
	const string orOperator = "||";
	const string scOperator = ";";

};

#endif
