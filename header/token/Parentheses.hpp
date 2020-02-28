#ifndef __PARENTHESES_HPP__
#define __PARENTHESES_HPP__

#include<iostream>
#include<string>

#include "Base.hpp"

using namespace std;

class Parentheses : public Base {

public:
	Parentheses(string param) {

		if(param == "("){

			isOpen = true;
			connectorID = "(";
		}
		else if(param == ")"){

			isOpen = false;
			connectorID = ")";
		}
	}

	/* Pure Virtual Functions */
	virtual string stringify(){

		if(isOpen == true){

			return "(";
		}

		return ")";
	}
	virtual bool execute(){

    return true;
  }
	virtual const string getID(){

		return connectorID;
	}

private:
	bool isOpen;
	string connectorID;

};

#endif  //__PARANTHESES_HPP__
