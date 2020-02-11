#ifndef __OR_HPP__
#define __OR_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

class Or : public Connector {

public:

	/* Constructors */
	Or(Base* lhs_, Base* rhs_):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){

		cout << lhs << "\n     " << "||" << "\n" << rhs;
	}
	virtual void execute(){

		if(lhs->execute() == false){

			if(rhs->execute() == false){


			}
		}
	}

private:

	Base* lhs;
	Base* rhs;
};

#endif __OR_HPP__
