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
	And(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		if(lhs->execute()){
			return rhs->execute();

		}

		return false;
	}

	virtual string stringify(){

		string cmdString = "(" + lhs->stringify() + " && " + rhs->stringify() + ")";

		return cmdString;
	}

	virtual const string getID(){

		return connectorID;
	}

	virtual void set_lhs(Base* left){

		if(lhs == nullptr){
			lhs = left;

		}
	}

	virtual void set_rhs(Base* right){
		if(rhs == nullptr){
			rhs = right;

		}
	}

	virtual Base* get_lhs(){

		return lhs;
	}
	virtual Base* get_rhs(){

		return rhs;
	}


private:
	Base* lhs;
	Base* rhs;
	const string connectorID = "&&";


};

#endif
