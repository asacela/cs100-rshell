#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "Connector.hpp"

class Semicolon : public Connector {

public:

	/* Constructors */
	Semicolon(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		if(lhs != nullptr){
			lhs->execute();
		}

		if(rhs != nullptr){
			return rhs->execute();
		}

		return false;
	}

	string stringify(){
		if(lhs != nullptr){
			if(rhs != nullptr){
				return lhs->stringify() + "; " + rhs->stringify();
			}
			return lhs->stringify() + ";";

		}
		return ";";

	}

private:
	Base* lhs;
	Base* rhs;


};

#endif //__SEMICOLON_HPP__
