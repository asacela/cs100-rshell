#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include<iostream>
#include<string>
#include<vector>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Base.hpp"

using namespace std;

class Command : public Base {

public:

	Command(const char** argList_) : argList(argList_) {}

	virtual void display(){

		cout << argList[0] << ":" << endl;

		for(int i = 1; argList[i] != nullptr; ++i){

			cout << "      " << argList[i] << endl;

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
		/*	if(execvp(argList[0], argList) < 0){

				return false;
			}*/
		}

		else{
			//waitpid
			while(wait(&status) != pid);
		}

		return true;
	}

private:

	const char** argList;
};

#endif  //__COMMAND_HPP__
