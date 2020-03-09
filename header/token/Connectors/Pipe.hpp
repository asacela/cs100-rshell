#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include<iostream>
#include<string>
#include<vector>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../Base.hpp"

using namespace std;

class Pipe : public Base {

public:

	/* Constructors */
	Pipe(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		//implement
		return false;
	}

	virtual string stringify(){

		string cmdString = lhs->stringify() + " | " + rhs->stringify();

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
	const string connectorID = "|";

};

#endif
