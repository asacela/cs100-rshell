#ifndef __AND_HPP__
#define __AND_HPP__

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class And : public Connector {

public:

	/* Constructors */
	And(Base* x1, Base* x2):lhs(x1),rhs(x2) {}

	/* Pure Virtual Functions */
	virtual void display(Base* lhs, Base* rhs){

		cout << lhs << "\n     " << connector << "\n" << rhs;
	}

	virtual void execute(Base* lhs, Base* rhs){

	}

private:

	string connector;
  Base* lhs;
  Base* rhs;

};

#endif
