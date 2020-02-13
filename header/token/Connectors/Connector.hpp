#ifndef __CONNECTOR_HPP__
#define __CONNNECTOR_HPP__

#include<iostream>
#include "../Base.hpp"

using namespace std;

class Connector : public Base {

public:

	/* Pure Virtual Functions */
	virtual void display() = 0;
	virtual bool execute() = 0;

protected:
	Base* lhs;
	Base* rhs;

};

#endif
