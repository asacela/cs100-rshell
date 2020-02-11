#ifndef __AND_HPP__
#define __AND_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

using namespace std;

class And : public Connector {

public:

	/* Constructors */
	And(Base* lhs_, Base* rhs_):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){

		cout << lhs->display() << "\n     " << "&&" << "\n" << rhs->display();
	}
	virtual void execute(){

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

#endif __AND_HPP__
