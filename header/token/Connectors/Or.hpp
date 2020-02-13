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
	virtual void display(){
		lhs->display();
		cout << "\n     " << "||" << "\n\n";
    rhs->display();

	}

	virtual bool execute(){

		if( !(lhs->execute()) ){
			return rhs->execute();

		}
		// else lhs->execute() == true
		return false;
	}

private:
	Base* lhs;
	Base* rhs;


};

#endif //__OR_HPP__
