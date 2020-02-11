#ifndef __OR_HPP__
#define __OR_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

class Or : public Base {

public:

	/* Constructors */
	Or(Base* lhs_, Base* rhs_):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){
		lhs->display();
		cout << "\n     " << "||" << "\n";
    rhs->display();

	}
	virtual bool execute(){

		if(lhs->execute() == false){

			if(rhs->execute() == false){


			}
		}
		return false;
	}

private:

	Base* lhs;
	Base* rhs;
};

#endif //__OR_HPP__
