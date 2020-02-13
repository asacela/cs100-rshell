#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include<iostream>
#include<string>
#include<vector>
#include<sys/types.h>
#include "Base.hpp"

using namespace std;

class Command : public Base {

public:

	/* Constructors */

	Command(char** argList_){

		argList = argList_;

	};

	/* Pure Virtual Functions */
	virtual void display(){

		cout << argList[0] << ": " << endl;


		int i = 1;
		while(argList[i] != '\0'){

			cout << "     " << argList[i] << endl;
		}
	}
	//incomplete
	virtual bool execute(){

		pid_t pid;
		int status;

		pid = fork();

		if(pid < 0){

			return false;
		}

		else if(pid == 0){
			if(execvp(argArray[0], argArray) < 0){

				return false;
			}
		}

		else{
			//waitpid
			while(wait(&status) != pid);
		}

		return true;
	}

private:

	char** argList;
};

#endif  //__COMMAND_HPP__
