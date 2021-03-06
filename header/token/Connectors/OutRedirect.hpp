#ifndef __OUTREDIRECT_HPP__
#define __OUTREDIRECT_HPP__

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

class OutRedirect : public Base {

public:

	/* Constructors */
	OutRedirect(string type, Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_),connectorID(type) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		const char* file = (rhs->stringify()).c_str();

		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;


		int savestdout = dup(1);

		int outputfd;
		if(connectorID == ">"){
			outputfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, mode);

		}
		else if(connectorID == ">>"){
			outputfd = open(file, O_WRONLY |  O_CREAT | O_APPEND, mode);

		}

		if(outputfd < 0){

			perror("open(2) file: Error");
			cout << rhs->stringify();
        	return false;
		}

		else if (dup2(outputfd,1) != STDOUT_FILENO) {

        	perror("dup(2)");
        	close(outputfd);
        	exit(EXIT_FAILURE);
    	}

		else{
			lhs->execute();
			close(outputfd);
			dup2(savestdout, 1);

		}

		//implement
		return true;
	}

	

	virtual string stringify(){

		string cmdString = lhs->stringify() + " " + connectorID + " " + rhs->stringify();

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
	const string connectorID;

};

#endif
