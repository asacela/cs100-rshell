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
	And(Base* lhs_, Base* rhs_):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){
    lhs->display();
		cout << "\n     " << "&&" << "\n";
    rhs->display();
	}
	virtual bool execute(){

		if(lhs->execute() == true){

			if(rhs->execute() == true){

				//
			}
		}
		else{

			//
		}
	}

private:


	Base* lhs;
	Base* rhs;
};

#endif //__AND_HPP__
