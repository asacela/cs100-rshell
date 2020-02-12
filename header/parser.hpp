#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<boost/tokenizer.hpp>

// #include "../header/token/Command.hpp"
#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Or.hpp"
#include "../header/token/Connectors/Semicolon.hpp"

using namespace std;
using namespace boost;

class Parser{

public:
	Parser(string cmdLine_) : cmdLine(cmdLine_) {
		parse();
		to_cstring();
		// assign();
	}

	const char** arguments(){ return argList; }

	// FIX THIS: Alec
	Base* objectify(vector<char**> paramList){

		Base* commandTemp;
		Base* connectorTemp;

		for(int i = 0; i < paramList.size(); i++){

			if(i == 1){
				
				commandTemp = new Command ((paramList.at(i - 1))); //at 0

				if((paramList.at(i))[0] == "&&"){

					connectorTemp = new And(commandTemp, (paramList.at(i + 1))); //at 2
				}
				else if(paramList.at(i)[0] == "||"){


					connectorTemp = new Or(commandTemp, (paramList.at(i + 1))); //at 2
				}

				else if((paramList.at(i)[0] == ";")){


					// add semicolon support
				}
			}
			else if((paramList.at(i))[0] == "&&"){


				commandTemp = new Command((paramList.at(i + 1)));
				connectorTemp = new And(connectorTemp, commandTemp);
			}

			else if((paramList.at(i))[0] == "||"){

				commandTemp = new Command((paramList.at(i + 1)));
				connectorTemp = new Or(connectorTemp, commandTemp);

			}

			else if((paramList.at(i))[0] == ";"){


			}
			else{

			}
		}


		return connectorTemp;		
	}

	void print(){
		if(argList[0] != '\0'){
			cout << argList[0];
		}
		for(int i = 1; argList[i] != '\0'; ++i){
			cout << '\n' << argList[i];
		}
	}




private:

	void parse(){

		bool isComment = false;
		for(int i = 0; i < cmdLine.size() && !isComment; ++i){

			char c = cmdLine.at(i);

			// If it is a comment
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

			// If it's a semicolon
			else if (c == ';'){
				cout << "FIX_ME: Semicolon" << endl;
			}

			// If it's a space
			else if(c != ' '){
				int end = cmdLine.find(' ',i);
				string str = cmdLine.substr(i,end - i);
				parsed.push_back(str);

				i = end - 1;
			}
			else{
				// Ignore white space
			}
		}

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


	void assign(){
		for(int i = 0; i < parsed.size(); ++i){
			// obj(i);
		}
	}
	// Helper function
	Base* obj(int i){

		if(parsed.at(i) == "&&"){
			Base* lhs = objList.at(i-1);
			Base* rhs =	obj(i+1);
			Base* andObj = new And(lhs,rhs);
			return andObj;
			objList.push_back(andObj);
		}
		else if(parsed.at(i) == "||"){
			Base* lhs = objList.at(i-1);
			Base* rhs =	obj(i+1);
			Base* orObj = new Or(lhs,rhs);
			objList.push_back(orObj);
			return orObj;

		}
		else{
			Base* argObj = nullptr;
			return argObj;

		}
	}




	// Private variables
	string cmdLine;
	vector<string> parsed;
	vector<Base*> objList;
	const char** argList;

};

#endif //__PARSER_HPP__
