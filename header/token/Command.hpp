#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include<iostream>
#include<string>
#include<vector>

class Command : public Base {

public:

	/* Constructors */
	Command(vector<string> cmdList){ 
		
		exec = cmdList.front();
		argList = cmdList.erase(cmdList.begin());
	};

	/* Pure Virtual Functions */
	virtual void display(){

		cout << exec << ": " << endl;

		for(int i = 0; i < argList.size(); i++){

			cout << "     " << argList.at(i) << endl;
		}

	}
	virtual int execute(){

		
	}

private:

	string exec;
	vector<string> argList;
};

#endif  //__COMMAND_HPP__