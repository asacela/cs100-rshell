#include <iostream>
#include <string>
#include "../header/token/Base.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	int num = 1;
	while(num){
		cout << "\n$ ";
		string cmdLine;
		getline(cin,cmdLine);

		Parser* parserObj = new Parser(cmdLine);
		Base* executable = parserObj->getSquashed();
		cout << executable->stringify() << endl;
		executable->execute();
	}

	return 0;
}
