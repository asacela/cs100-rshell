#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "Connector.hpp"

class Semicolon : public Connector {

public:

	/* Constructors */
	Semicolon(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){
		lhs->display();
		cout << "\n     " << ";" << "\n";
    rhs->display();

	}

	virtual bool execute(){

		if(lhs != nullptr){
			lhs->execute();
		}

		if(rhs != nullptr){
			return rhs->execute();
		}
		
		return false;
	}

};

#endif //__SEMICOLON_HPP__
