#ifndef __PIPE_HPP__
#define __PIPE_HPP__

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

class Pipe : public Base {

public:

	/* Constructors */
	Pipe(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {}

	/* Pure Virtual Functions */
	virtual bool execute(){

		int pipefd[2];
		int pid1;
		int pid2;

		int status;

		pipe(pipefd);

		// Process 1
		pid1 = fork();
		if(pid1 < 0){

			perror("rshell: error forking child process");
			return false;
		}

		else if(pid1 == 0)
		{

			dup2(pipefd[0], 0);
			close(pipefd[1]);
			lhs->execute();
		}

		else{

			pid_t check = wait(&status);
			while(check != pid1);
		}


		// Process 2
		pid2 = fork();
		if(pid2 < 0){
			
			perror("rshell: error forking child process");
			return false;
		}

		else if(pid2 == 0)
		{

			dup2(pipefd[1], 1);

			close(pipefd[0]);

			rhs->execute();

			return true;
		}

		else
		{

			pid_t check = wait(&status);
			while(check != pid2);
		}

		return false;
	}

	virtual string stringify(){

		string cmdString = lhs->stringify() + " | " + rhs->stringify();

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
	const string connectorID = "|";

};

#endif
