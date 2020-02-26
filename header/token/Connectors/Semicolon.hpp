#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

using namespace std;

class Semicolon : public Base {

public:

	/* Constructors */
	Semicolon(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		bool left = true;
		if(lhs != nullptr){
			if(lhs->getID() == "cmd" && !lhs->getCommands().empty()){
				left = lhs->execute();
			}
			else if(lhs->getID() != "cmd"){
				left = lhs->execute();
			}
		}

		if(rhs != nullptr){
			if(rhs->getID() == "cmd" && !rhs->getCommands().empty()){
				return rhs->execute();
			}
			else if(rhs->getID() != "cmd"){
				return rhs->execute();
			}
		}
		if(lhs != nullptr){

			return left;
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
			if(rhs->getID() == "cmd" && !rhs->getCommands().empty()){
				cmdString += " " + rhs->stringify();

			}
			else if(rhs->getID() != "cmd"){
				cmdString += " " + rhs->stringify();

			}
		}

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
	const string connectorID = ";";


};

#endif
