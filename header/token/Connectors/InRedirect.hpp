#ifndef __IN_REDIRECT_HPP__
#define __IN_REDIRECT_HPP__

#include<iostream>
#include<string>
#include<vector>
#include <unistd.h>
#include "../Base.hpp"

using namespace std;

class InRedirect : public Base {

public:

	/* Constructors */
	InRedirect(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		string fileName = rhs->stringify();
		int o_flag = O_WRONLY | O_CREAT | O_TRUNC;
		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;


		int savestdin = dup(0);

		int outputfd = open(fileName, o_flag, mode);

		if(fd < 0){

			perror("open(2) file: " OUTPATH);
        	return false;
		}

		else if (dup(outputfd) != STDOUT_FILENO) {

        	perror("dup(2)");
        	close(outputfd);
        	exit(EXIT_FAILURE);
    	}

		else{

			lhs->execute();
		}

		close(fd);

		dup2(savestdin, 0);


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

		lhs = left;

	}

	virtual void set_rhs(Base* right){

		rhs = right;
	}


private:
	Base* lhs;
	Base* rhs;
	const string connectorID = "<";

};

#endif
