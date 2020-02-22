#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

class Semicolon : public Base {

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

		return true;
	}

	virtual string stringify(){
		string cmdString = "";

		if(lhs != nullptr){
			cmdString += lhs->stringify();
		}
		
		cmdString += ";";
		
		if(rhs != nullptr){
			cmdString += " " + rhs->stringify();
		}
    
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
