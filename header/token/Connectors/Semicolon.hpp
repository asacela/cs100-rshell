#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

class Semicolon : public Base {

public:

	/* Constructors */
	Semicolon(Base* lhs_, Base* rhs_):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){

	}

	virtual bool execute(){


	}

private:

	Base* lhs;
	Base* rhs;
};

#endif //__SEMICOLON_HPP__
