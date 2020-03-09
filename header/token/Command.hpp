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
	Command(){}

	virtual ~Command() {
		delete [] argList;
	}

	//incomplete
	virtual bool execute(){

		// Check for exit
		if(parsed.size() != 0){
			if(parsed.front() == "exit"){
				exit(0);
			}
		}


		pid_t pid;
		int status;

		pid = fork();

		if(pid < 0){
			perror("rshell: error forking child process");
			return false;
		}

		else if(pid == 0){
			if(execvp(argList[0], (char**)argList) < 0){
  			perror("rshell: exec failed: ");
				// printf("*** ERROR: exec failed\n");
				printf("rshell: command not found: ");
				cout << parsed.at(0) << endl;
			 	// return false;
				exit(1);

			}

		}


		// Look into this
		else{
			pid_t check = wait(&status);
			while(check != pid);

		}

		perror("rshell: called");

		for(int i = 0; i < parsed.size(); ++i){

		 	cout << parsed.at(i) << " ";
		}


		cout << " [status-code:  " << status << "]" << endl;

		//Failed Status Code for Hammer: 512, for Local: 256
		if(status == 512 || status == 256){

			// perror(" failed");
			return false;
		}

		perror(" succeeded");

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

	virtual vector<string> getCommands(){

		return parsed;
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

	vector<string> parsed;
	const char** argList;
	const string connectorID = "cmd";
};

#endif  //__COMMAND_HPP__
