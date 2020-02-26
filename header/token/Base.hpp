#ifndef __BASE_HPP__
#define __BASE_HPP__

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Base {

public:
	virtual ~Base() {}

	/* Pure Virtual Functions */
	virtual string stringify() = 0;
	virtual bool execute() = 0;
	virtual const string getID() = 0;

	/* Virtual Functions */
	virtual vector<string> getCommands(){
		vector<string> temp;
		return temp;
	}
	virtual void set_lhs(Base* lhs){

		// leave empty
	}
	virtual void set_rhs(Base* rhs){

		// leave empty
	}

	virtual Base* get_lhs(){

		return nullptr;
	}
	virtual Base* get_rhs(){

		return nullptr;
	}

};

#endif  //__BASE_HPP__
