#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
		if(parser.size() == 3){

			int status = stat((char*)(*argList[2]), struct stat *buf);
			bool result = false;

			string flag = parser.at(1);
			if(flag == "-e"){
				result = exists();
			}
			else if(flag == "-d"){
				result = isDir();
			}
			else if(flag == "-f"){
				result = isFile();
			}
			else{
				// Unknown flag
			}

	    bool test = Command::execute();
	    if(result){
	      cout << "(TRUE)" << "\n";
	    }
	    else{
	      cout << "(FALSE)" << "\n";
	    }

			return true;
		}

    return false;
	}


private:
	bool isDir(m){

		return S_ISDIR(m);
	}

	bool isFile(m){

		return S_ISREG(m);
	}

	bool exists(m){

		return S_ISREG(m) || S_ISDIR(m);
	}

};

#endif
