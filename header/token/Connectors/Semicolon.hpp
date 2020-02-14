#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

class Semicolon : public Connector {

public:

	/* Constructors */
	Semicolon(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		if(lhs != nullptr){
			lhs->execute();
		}

		if(rhs != nullptr){
			return rhs->execute();
		}

		return false;
	}

	virtual string stringify(){
		string cmdString;



		if(lhs != nullptr){
			if(rhs != nullptr){

				cmdString = lhs->stringify() + "; " + rhs->stringify();

				return cmdString;
			}

			cmdString = lhs->stringify() + "; ";

			return cmdString;

		}
		cmdString = ";";

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
	const string connectorID = ";";


};

#endif
