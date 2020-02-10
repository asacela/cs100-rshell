#ifndef __BASE_HPP__
#define __BASE_HPP__

#include<iostream>
#include<string>

class Base(){

public:

	/* Constructors */
	Base(){ };

	/* Pure Virtual Functions */
	virtual void Execute() = 0;
};

#endif  //__BASE_HPP__