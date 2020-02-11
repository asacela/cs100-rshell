#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

class Semicolon : public Connector {

public:

	/* Constructors */
	And(Base* lhs_, Base* rhs_):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual void display(){

	}

	virtual void execute(){


	}

private:

	Base* lhs;
	Base* rhs;
};

#endif __SEMICOLON_HPP__
