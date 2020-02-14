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

	Parser(string cmdLine_) : cmdLine(cmdLine_) {

		oldParsedSize = 0;
		parse();
	}

	void parse(){

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
				if(i+1 <= end-i-1){
					str = cmdLine.substr(i + 1,end - i - 1);
					parsed.push_back(str);
				}
				i = end;
			}

			// If it's not a space
			else if(c != ' '){

				// Look for next appreance of a space
				size_t end = cmdLine.find(' ',i);

				// If no other space found -> have reached the end of cmdLine string
				if(end == string::npos){

					// Create substring
					end = cmdLine.size();
					str = cmdLine.substr(i,end - i);
					// If very last character of sub string is semicolon
					if(str.back() == ';'){
						// Remove semicolon from sub string, push into parsed, make obj
						str.pop_back();
						if(str != ""){
							parsed.push_back(str);
						}
						objectify(";");
						i = end;

					}
					// Else that is the end of the string
					else{
						parsed.push_back(str);

						objectify("list");
						i = end;
					}
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
						objectify(";");
						i = end;

					}
					else if(str == "&&"){
						objectify("&&");
						i = end;

					}
					else if(str == "||"){
						objectify("||");
						i = end;

					}
					// Else it is a regular command -> continue
					else {
						parsed.push_back(str);

						i = end - 1;
					}
				}

			}

		}

		// Base cases: you reach the end of the string (i.e. no more connectors)
		// No arguments received
		if(parsed.size() == 0){

			return;
		}

		objectify("list");
		return;
	}

	void test(){
		cout << endl << "--TEST--" << endl;
		cout << "parsed: (size "<<parsed.size()<<")" << endl;
		for(int i = 0; i < parsed.size(); ++i){
			// cout << baseList.at(i)->ID();
			cout << parsed.at(i) << " ";

		}
		cout << endl << "baseList: (size "<<baseList.size()<<")" << endl;
	}

	Base* getSquashed(){

		Base* squashed = squash(baseList);
		return squashed;
	}


private:

	void objectify(string objType){

		Base* objTemp = nullptr;
		Base* lhs = nullptr;

		// Populate subParse with newly read strings
		vector<string> subParsed;
		for(int i = oldParsedSize; i < parsed.size(); ++i){
			subParsed.push_back(parsed.at(i));
		}
		updateSize();

		// If there exists new commands
		if(subParsed.size() != 0){
			lhs = new Command(subParsed);

		}

		// Check if parsed is to exit
		if(subParsed.size() == 1){
			if(subParsed.at(0) == "exit"){
				// delete lhs;
				lhs = new Exit(subParsed);
			}
		}

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

		if(lhs != nullptr){
			baseList.push_back(lhs);
		}
		if(objTemp != nullptr && objTemp != lhs){
			baseList.push_back(objTemp);
		}
	}


	void updateSize(){
		oldParsedSize = parsed.size();
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
	int oldParsedSize;

	const string andOperator = "&&";
	const string orOperator = "||";
	const string scOperator = ";";

};

#endif
