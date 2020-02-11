#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<boost/tokenizer.hpp>

#include "../header/token/Base.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Connector.hpp"
#include "../header/execute.hpp"

using namespace std;
using namespace boost;

class parser{

public:
	parser(string cmdLine) : cmdLine(cmdLine) {
		parse();
		assign();
	}

	vector<string> stringify(){ return cmdList; }


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
				end = cmdLine.find('\"',i);
				str = cmdLine.substr(i + 1,end - i - 1);
			}
			else if (c == ';'){
				cout << "FIX ME" << endl;
			}
			else if(c != ' '){
				end = cmdLine.find(' ',i);
				str = cmdLine.substr(i,end - i);
			}
			else{
				// Ignore white space
			}
		}

	}


	void assign(){
		for(int i = 0; i < cmdList.size(); ++i){
			obj(i);
		}
	}

	void obj(int i){

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
};
