#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Base.hpp"

using namespace std;

class Command : public Base {

public:

	Command(vector<string> parsed_) : parsed(parsed_){
		to_cstring();
	}

	//incomplete
	virtual bool execute(){

		pid_t pid;
		int status;

		pid = fork();

		if(pid < 0){
			printf("*** ERROR: forking child process failed\n");
			return false;
		}

		else if(pid == 0){
			if(execvp(argList[0], (char**)argList) < 0){
				printf("*** ERROR: exec failed\n");
			 	return false;
			}
		}

		else{
			while(wait(&status) != pid);
		}

		printf("*** EXECVP CALLED: ");

		for(int i = 0; i < parsed.size(); ++i){

			cout << parsed.at(i) << " ";
		}


		cout << " [status-code:  " << status << "]";
		if(status == 256){

			printf(" failed\n");
			return false;
		}

		printf(" succeeded\n");

		return true;
	}

	virtual string stringify(){
		string str;
		if(parsed.size() != 0){
			str = parsed.at(0);
			for(int i = 1; i < parsed.size(); ++i){
				str = str + " " + parsed.at(i);
			}
		}

		return str;
	}

	virtual const string getID(){

		return connectorID;
	}

protected:

	void to_cstring(){
		int size = parsed.size();

		argList = new const char*[size+1];
		argList[size] =  nullptr;

		// Populate the argList variable with c_string copies of the parsed
		for(int i = 0; i < size; ++i){
			argList[i] = parsed.at(i).c_str();

		}

	}


private:
	vector<string> parsed;
	const char** argList;
	const string connectorID = "cmd";
};

#endif  //__COMMAND_HPP__
