#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<boost/tokenizer.hpp>

#include "../header/token/Command.hpp"
#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Or.hpp"
#include "../header/token/Connectors/Semicolon.hpp"

using namespace std;
using namespace boost;

class Parser{

public:
	Parser(string cmdLine_) : cmdLine(cmdLine_) {
		parse();
		cstring();
		// assign();
	}

	char ** arguments(){ return argList; }

	// FIX THIS: Alec
	vector<Base*> objectify(){ return objList; }


private:

	void parse(){

		bool isComment = false;

		for(int i = 0; i < cmdLine.size() && !isComment; ++i){
			char c = cmdLine.at(i);
			if(c == '#'){
				isComment = true;
			}
			else if(c == '\"'){
				int end = cmdLine.find('\"',i);
				string str = cmdLine.substr(i + 1,end - i - 1);
				cmdList.push_back(str);
			}
			else if (c == ';'){
				cout << "FIX ME" << endl;
			}
			else if(c != ' '){
				int end = cmdLine.find(' ',i);
				string str = cmdLine.substr(i,end - i);
				cmdList.push_back(str);
			}
			else{
				// Ignore white space
			}
		}

	}


	void cstring(){
		int size = cmdList.size();

		argList = new char*[size];

		// Populate the argList variable with c_string copies of the cmdList
		for(int i = 0; i < size; ++i){
			strcpy(argList*[i],cmdList.at(i).c_str());

		}

	}


	void assign(){
		for(int i = 0; i < cmdList.size(); ++i){
			// obj(i);
		}
	}

	Base* obj(int i){

		if(cmdList.at(i) == "&&"){
			Base* lhs = objList.at(i-1);
			Base* rhs =	obj(i+1);
			And* andObj = new And(lhs,rhs);
			objList.push_back(andObj);

		}
		else if(cmdList.at(i) == "||"){
			Base* lhs = objList.at(i-1);
			Base* rhs =	obj(i+1);
			Or* orObj = new Or(lhs,rhs);
			objList.push_back(orObj);

		}
	}

	string cmdLine;
	vector<string> cmdList;
	vector<Base*> objList;
	char** argList;
};

#endif //__PARSER_HPP__
