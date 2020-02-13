#ifndef __OR_HPP__
#define __OR_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "Connector.hpp"

class Or : public Connector {

public:

	/* Constructors */
	Or(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		if( !(lhs->execute()) ){
			return rhs->execute();

		}
		// else lhs->execute() == true
		return false;
	}

	virtual string stringify(){

		return lhs->stringify() + " || " + rhs->stringify();
	}

private:
	Base* lhs;
	Base* rhs;


};

#endif //__OR_HPP__
