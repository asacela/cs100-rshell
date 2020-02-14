#ifndef __OR_HPP__
#define __OR_HPP__

#include<iostream>
#include<string>
#include<vector>

#include "../Base.hpp"

class Or : public Base {

public:

	/* Constructors */
	Or(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		if(!lhs->execute()){

			if(rhs->execute()){

				return true;
			}
			return false;
		}
		return true;
	}

	virtual string stringify(){


		string cmdString = lhs->stringify() + " || " + rhs->stringify();

		return cmdString;
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
	const string connectorID = "||";


};

#endif
