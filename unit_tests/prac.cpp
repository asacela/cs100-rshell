#include <iostream>
#include <string>
// #include "../header/token/Command.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	cout << "$ ";
	string cmdLine;
	getline(cin,cmdLine);

	Parser* list = new Parser(cmdLine);

	const char** arguments = list->arguments();

	if(arguments[0] != '\0'){
		cout << arguments[0];
	}
	for(int i = 1; arguments[i] != '\0'; ++i){
		cout << '\n' << arguments[i];
	}



	return 0;
}
