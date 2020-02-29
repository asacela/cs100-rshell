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

class Tester : public Command {

public:

	/* Constructors */
	Tester(vector<string> parsed_) : Command(){

		parsed = parsed_;

        if(!parsed.empty()){
            if(parsed.front() == "[" && parsed.back() == "]"){
                vector<string>::iterator it = parsed.begin();
                parsed.erase(it);
                parsed.pop_back();
            }

            if(parsed.front() != "test"){
                vector<string>::iterator it = parsed.begin();
                parsed.insert(it,"test");
            }

            if(parsed.size() >= 2){

                if(parsed.at(1).front() != '-'){
                vector<string>::iterator it = parsed.begin();
                parsed.insert(it+1,"-e");
                }
            }
        }


        to_cstring();

	}

	/* Pure Virtual Functions */
	virtual bool execute(){
        struct stat sb;

		if(parsed.size() == 3){



			if(stat(argList[2], &sb) < 0){

                perror("rshell: error in running stat()");
                cout << "(FALSE)" << "\n";

                return true;
            }

			bool result = false;

			string flag = parsed.at(1);
			if(flag == "-e"){
				result = exists(sb.st_mode);
			}
			else if(flag == "-d"){
				result = isDir(sb.st_mode);
			}
			else if(flag == "-f"){
				result = isFile(sb.st_mode);
			}
			else{
				// Unknown flag
			}

	    // bool test = Command::execute();
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
	bool isDir(mode_t m){

        if(S_ISDIR(m) > 0){
            return true;
        }

		return false;
	}

	bool isFile(mode_t m){

		if(S_ISREG(m) > 0){
            return true;
        }

        return false;
	}

	bool exists(mode_t m){

        if(S_ISDIR(m) > 0 || S_ISREG(m) > 0){
            return true;
        }

        return false;
	}

};

#endif
