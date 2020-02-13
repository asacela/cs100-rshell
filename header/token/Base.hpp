#ifndef __BASE_HPP__
#define __BASE_HPP__

#include<iostream>
#include<string>

using namespace std;

class Base {

public:

	/* Pure Virtual Functions */
	virtual string stringify() = 0;
	virtual bool execute() = 0;
	virtual const string getID() = 0;

	/* Virtual Functions */
	virtual void set_lhs(Base* lhs){

		// leave empty
	}
	virtual void set_rhs(Base* rhs){

		// leave empty
	}

};

#endif  //__BASE_HPP__
