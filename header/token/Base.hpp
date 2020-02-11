#ifndef __BASE_HPP__
#define __BASE_HPP__

#include<iostream>
#include<string>

using namespace std;

class Base {

public:

	/* Pure Virtual Functions */
	virtual void display() = 0;
	virtual bool execute() = 0;
};

#endif  //__BASE_HPP__
