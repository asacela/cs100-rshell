#ifndef __AND_HPP__
#define __AND_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "../Base.hpp"

using namespace std;

class And : public Connector {

public:

	/* Constructors */
	And(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		lhs->execute();
		return rhs->execute();
	}

	virtual string stringify(){

		return lhs->stringify() + " && " + rhs->stringify();
	}

private:
	Base* lhs;
	Base* rhs;

};

#endif
