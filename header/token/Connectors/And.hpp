#ifndef __AND_HPP__
#define __AND_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

using namespace std;

class And : public Base {

public:

	/* Constructors */

	/* Pure Virtual Functions */
	virtual bool execute(){

		if(lhs->execute()){

			if(rhs->execute()){

				return true;
			}
		}

	}

	virtual const string getID(){

		return connectorID;
	}

	virtual void set_lhs(Base* left){

		lhs = left;

	}

	virtual void set_rhs(Base* right){

		rhs = right;
	}


private:
	Base* lhs;
	Base* rhs;
	const string connectorID = "&&";

};

#endif
