#ifndef __EXIT_HPP__
#define __EXIT_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "Command.hpp"

using namespace std;

class Exit : public Command {

public:

	/* Constructors */
	Exit(vector<string> parsed_) : Command(parsed_) {
		to_cstring();
	}

	/* Pure Virtual Functions */
	virtual bool execute(){
    exit(0);
    return true;
	}

private:
	vector<string> parsed;
  const char** argList;
};

#endif
