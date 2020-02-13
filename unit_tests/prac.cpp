#include <iostream>
#include <string>
#include "../header/token/Command.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	cout << "$ ";
	string cmdLine;
	getline(cin,cmdLine);

	Parser* list = new Parser(cmdLine);

	char** arguments = list->arguments();

	for(int i = 0; arguments[i] != '\0'; ++i){
		cout << arguments[i] << "\n";

	}

	Base* n = new Command(arguments);

	n->execute();



	return 0;
}
