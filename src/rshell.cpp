#include <iostream>
#include <string>
#include "../header/token/Base.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	int run = 1;
	while(run){
		cout << "\n$ ";
    
		string cmdLine;
		getline(cin,cmdLine);

		Parser* parserObj = new Parser(cmdLine);
		Base* executable = parserObj->getSquashed();

		if(executable != nullptr){
			executable->execute();
		}
		delete parserObj;

	}

	return 0;
}
