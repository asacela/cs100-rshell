#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "Base.hpp"

using namespacestd;

class Connector : public Base {

public:

	/* Pure Virtual Functions */
	virtual void display() = 0;
	virtual void execute() = 0;
};

#endif  //__CONNECTOR_HPP__
