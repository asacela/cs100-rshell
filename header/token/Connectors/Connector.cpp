#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__

#include<iostream>
#include<string>
#include<vector>

using namespacestd;

class Connector : public Base {

public:

	/* Constructors */
	Connector(string connector_){

		connector = connector_;
	};

	/* Pure Virtual Functions */
	virtual void display(Base* lhs, Base* rhs){

		cout << lhs << "\n     " << connector << "\n" << rhs;
	}

	virtual void execute(Base* lhs, Base* rhs){

	}

private:

	string connector;
};

#endif  //__CONNECTOR_HPP__
