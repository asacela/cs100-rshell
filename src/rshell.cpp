#include <iostream>
#include <string>
#include "../header/token/Base.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	int num = 0;
	while(num){
		cout << "$ ";
		string cmdLine;
		getline(cin,cmdLine);

		Parser* parserObj = new Parser(cmdLine);

	}

	return 0;
}
