#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<cstring>

#include "../header/token/Base.hpp"
#include "../header/token/Command.hpp"
#include "../header/token/Test.hpp"
#include "../header/token/Parentheses.hpp"
#include "../header/token/Connectors/And.hpp"
#include "../header/token/Connectors/Or.hpp"
#include "../header/token/Connectors/Semicolon.hpp"

using namespace std;


class Parser{

public:

	Parser(string cmdLine_ = "") : cmdLine(cmdLine_) {

		oldParsedSize = 0;
		parse();
	}

	~Parser() {
		while(!baseList.empty()){
			delete baseList.back();
			baseList.pop_back();
		}

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
				if(i+1 < end){
					str = cmdLine.substr(i + 1,end - (i+1));
					parsed.push_back(str);
				}
				i = end;
			}

			// If it's an open parenthese
			else if(c == '('){

				objectify("(");
			}

			// If it's not a space
			else if(c != ' '){

				// Look for next appreance of a space
				size_t end = cmdLine.find(' ',i);

				// If no other space found -> have reached the end of cmdLine string
				if(end == string::npos){
					end = cmdLine.size();
				}

				// Create substring
				str = cmdLine.substr(i,end - i);

				if(str == "&&"){
					objectify("&&");

				}
				else if(str == "||"){
					objectify("||");

				}
				// If very last character of sub string is ';' or ')'
				else if(str.back() == ';' || str.back() == ')'){

					// If the char before the space is ';'
					bool hadSemi = false;
					if(str.back() == ';'){
						// Remove semicolon from sub string
						hadSemi = true;
						str.pop_back();

					}

					// Remove all ')' at end of str
					int numParentheses = 0;
					while(str.back() == ')'){
						++numParentheses;
						str.pop_back();

					}

					if(str != ""){
						parsed.push_back(str);

					}
					for(int j = 0; j < numParentheses; ++j){
						objectify(")");

					}
					if(hadSemi){
						objectify(";");

					}

				}
				// Else regular command
				else{
					parsed.push_back(str);

				}

				i = end;

			}

		}

		// No arguments received
		if(parsed.empty()){
			return;
		}

		// Push_back the rest of the commands
		objectify("list");
		return;
	}

	Base* getSquashed(){


		return squash(precedence(baseList));
	}

	Base* testSquashed(vector<Base*> objectList){


		return squash(precedence(objectList));
	}

	vector<Base*> test(){
		cout << endl << "--TEST--" << endl;
		cout << "parsed: (size "<<parsed.size()<<")" << endl;
		for(int i = 0; i < parsed.size(); ++i){
			cout << parsed.at(i) << " ";

		}
		cout << endl << "baseList: (size "<<baseList.size()<<")" << endl;

		return baseList;
	}


private:

	void objectify(string objType){

		Base* objTemp = nullptr;
		Base* lhs = nullptr;

		// Populate subParse with newly read strings
		vector<string> subParsed;
		// cout << "oldParsedSize: " << oldParsedSize << endl;	// ------------------------------------------------
		// cout << "parsedSize: " << parsed.size() << endl;		// ------------------------------------------------

		for(int i = oldParsedSize; i < parsed.size(); ++i){
			subParsed.push_back(parsed.at(i));
		}
		updateSize();

		// cout << "subParsedSize: " << subParsed.size() << endl; // ------------------------------------------------

		// If there exists new commands
		if(!subParsed.empty()){
			lhs = new Command(subParsed);

			if(subParsed.front() == "test" || (subParsed.front() == "[" && subParsed.back() == "]")){
				delete lhs;
				lhs = new Test(subParsed);

			}
			// cout << lhs->getID() << endl; // ------------------------------------------------
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
		else if(objType == "("){

			objTemp = new Parentheses("(");
		}
		else if(objType == ")"){

			objTemp = new Parentheses(")");
		}
		else if(objType == "list"){

			objTemp = lhs;
		}

		if(lhs != nullptr){
			baseList.push_back(lhs);
			// cout << baseList.back()->getID() << endl; // ------------------------------------------------

		}
		if(objTemp != nullptr && objTemp != lhs){
			baseList.push_back(objTemp);

		}

		if(!baseList.empty()){
			// cout << baseList.back()->getID() << endl; // ------------------------------------------------

		}
		// cout << "baseListSize: " << baseList.size() << endl << endl; // ------------------------------------------------


	}

	void updateSize(){

		oldParsedSize = parsed.size();
	}

	vector<Base*> precedence(vector<Base*> objectList){
		stack<int> parStack;
		int index = 0;
		Base* squashedObj = nullptr;
		// cout << "--Precedence--" << endl; // ------------------------------------------------
		// cout << "BEFORE:" << endl; // ------------------------------------------------
		for(int i = 0; i < objectList.size(); ++i){
			string ID = objectList.at(i)->getID();
			// cout << "ID:" << ID << endl; // ------------------------------------------------
		}


		// Search for parenthese and squash everything in between
		for(int i = 0; i < objectList.size(); ++i){
			string ID = objectList.at(i)->getID();

			if(ID == "("){
				parStack.push(i);

			}
			else if(ID == ")"){
				if(parStack.empty()){
					cout << "rshell: Error: Invalid number of parenthese\n";
					exit(1);
				}
				index = parStack.top();
				// cout << "\'(\' index:" << index << endl; // ------------------------------------------------

				parStack.pop();

				// Fill in new temp list
				vector<Base*> tempList;
				for(int j = index+1; j < i; ++j){
					tempList.push_back(objectList.at(j));

				}

				// Delete old objects from objectList
				vector<Base*>::iterator it = objectList.begin();
				objectList.erase(it + index, it + i + 1);

				// Insert squashed version of the new temp list
				if(!tempList.empty()){
					it = objectList.begin();
					squashedObj = squash(tempList);
					objectList.insert(it + index, squashedObj);

				}

				i = index;

			}
		}

		// cout << "AFTER:" << endl; // ------------------------------------------------
		for(int i = 0; i < objectList.size(); ++i){
			string ID = objectList.at(i)->getID();
			// cout << "ID:" << ID << endl; // ------------------------------------------------
		}

		if(!parStack.empty()){
			cout << "rshell: Error: Invalid number of parenthese\n";
			exit(1);
		}

		return objectList;
	}

	Base* squash(vector<Base*> objectList){

		// cout << "--Squash--" << endl; // ------------------------------------------------
		// cout << "objectListSize: "<< objectList.size() << endl; // ------------------------------------------------


		Base* squashed = nullptr;


		for(int i = 0; i < objectList.size(); ++i){

			// string ID = objectList.at(i)->getID();// ------------------------------------------------


			try{
				Base* currObj = objectList.at(i);
				string ID = currObj->getID();

				if(i == 0){
					squashed = currObj;

					if(ID == ";"){
						Base* dummyCmd = new Command({});
						currObj->set_lhs(dummyCmd);

						if(i != objectList.size() - 1){
							currObj->set_rhs(objectList.at(i + 1));
						}
					}

				}
				if (ID == "&&" || ID == "||" || ID == ";"){
					if(i != 0){
						currObj->set_lhs(squashed);
					}
					if(i != objectList.size() - 1){
						currObj->set_rhs(objectList.at(i + 1));
					}

					if(ID == ";" && i == objectList.size() - 1){
						Base* dummyCmd = new Command({});
						currObj->set_rhs(dummyCmd);

					}

					if(currObj->get_lhs() == squashed){
						squashed = currObj;
					}

				}
			}
			catch(const std::out_of_range& e){

				cout << "out_of_range ERROR:" << e.what() << endl;
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
