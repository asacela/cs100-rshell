#ifndef __INREDIRECT_HPP__
#define __INREDIRECT_HPP__

#include<iostream>
#include<string>
#include<vector>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../Base.hpp"

using namespace std;

class InRedirect : public Base {

public:

	/* Constructors */
	InRedirect(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		const char* file = (rhs->stringify()).c_str();

		int savestdin = dup(0);

		int inputfd = open(file, O_RDONLY);

		if(inputfd < 0){

			perror("open(2) file: Error");
			cout << rhs->stringify();
        	return false;
		}

		else if (dup2(inputfd,0) != STDIN_FILENO) {

        	perror("dup(2)");
        	close(inputfd);
        	exit(EXIT_FAILURE);
    	}

		else{

			lhs->execute();
			close(inputfd);
			dup2(savestdin, 0);
		}

		//implement
		return true;
	}

	virtual string stringify(){

		string cmdString = lhs->stringify() + " < " + rhs->stringify();

		return cmdString;
	}

	virtual const string getID(){

		return connectorID;
	}

	virtual void set_lhs(Base* left){
		if(lhs == nullptr){
			lhs = left;
		}
	}

	virtual void set_rhs(Base* right){
		if(rhs == nullptr){
			rhs = right;
		}
	}

	virtual Base* get_lhs(){

		return lhs;
	}
	virtual Base* get_rhs(){

		return rhs;
	}


private:
	Base* lhs;
	Base* rhs;
	const string connectorID = "<";

};

#endif
