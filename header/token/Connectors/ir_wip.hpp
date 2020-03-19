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
	InRedirect(Base* lhs_ = nullptr, Base* rhs_ = nullptr):lhs(lhs_),rhs(rhs_) {

		to_cstring(lhs->getCommands());
	}

	

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

			pid_t pid;
			int status;

			pid = fork();

			if(pid < 0){
				perror("rshell: error forking child process");
				return false;
			}

			else if(pid == 0){
				if(execlp(argList[0], argList, nullptr) < 0){
	  			perror("rshell: exec failed: ");
					// printf("*** ERROR: exec failed\n");
					printf("rshell: command not found: ");
					cout << argList[0] << endl;
				 	// return false;
					exit(1);

				}

			}


			// Look into this
			else{
				pid_t check = wait(&status);
				while(check != pid);

			}

			perror("rshell: InRedirect: ");
			cout << " [status-code:  " << status << "]" << endl;

			//Failed Status Code for Hammer: 512, for Local: 256
			if(status == 512 || status == 256){

				// perror(" failed");
				return false;
			}

			perror(" succeeded");

			return true;
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

		lhs = left;

	}

	virtual void set_rhs(Base* right){

		rhs = right;
	}


private:
	Base* lhs;
	Base* rhs;
	const string connectorID = "<";
	const char** argList;
	const char** to_cstring(vector<string> parsed){
		int size = parsed.size();

		const char** argList = new const char*[size+1];
		argList[size] =  nullptr;

		// Populate the argList variable with c_string copies of the parsed
		for(int i = 0; i < size; ++i){
			argList[i] = parsed.at(i).c_str();

		}

		return argList;

	}

};

#endif