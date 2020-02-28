#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <string>
#include <vector>
#include "Command.hpp"

using namespace std;

class Test : public Command {

public:

	/* Constructors */
	Test(vector<string> parsed_) : Command(parsed_) {

    if(parsed.size() != 0){
      if(parsed.front() == "[" && parsed.back() == "]"){
        vector<string>::iterator it = parsed.begin();
        parsed.erase(it);
        parsed.pop_back();
      }

      if(parsed.front() != "test"){
        vector<string>::iterator it = parsed.begin();
        parsed.insert(it,"test");
      }

      if(parsed.at(1).front() != '-'){
        vector<string>::iterator it = parsed.begin();
        parsed.insert(it+1,"-e");
      }
    }


    to_cstring();
	}

	/* Pure Virtual Functions */
	virtual bool execute(){
    bool test = Command::execute();
    if(test){
      cout << "(TRUE)" << "\n";
    }
    else{
      cout << "(FALSE)" << "\n";
    }
    return test;
	}

private:
	vector<string> parsed;
  const char** argList;
};

#endif
