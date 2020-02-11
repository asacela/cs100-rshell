#ifndef __BASE_HPP__
#define __BASE_HPP__

#include<iostream>
#include<string>

using namespace std;

class Base {

public:

	/* Constructors */
	Base(){ };

	/* Pure Virtual Functions */
	virtual void display() = 0;
	virtual void execute() = 0;
};

#endif  //__BASE_HPP__
