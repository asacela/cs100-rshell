#ifndef __EXIT_HPP__
#define __EXIT_HPP__

#include<iostream>
#include<string>
#include<vector>
#include "Command.hpp"

class Exit : public Command {

public:

	/* Constructors */
	Exit(char** argList_){

    argList = argList_;

	};

	/* Pure Virtual Functions */
	virtual bool execute(){
    exit(0);
    return true;
	}

private:
  char** argList;
};

#endif
