#include <iostream>
#include <string>
#include "../header/token/Command.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	cout << "$ ";
	string cmdLine;
	getline(cin,cmdLine);

	parser* list = new parser(cmdLine);
	int length = 1;

	vector<string> vec1 = list->stringify();
	for(int i = 0; i < vec1.size(); ++i){
		cout << vec1.at(i) << endl;
	}

	vector<Base*> vec2 = list->objectify();
	for(int i = 0; i < vec2.size(); ++i){
		cout << vec2.at(i)->display() << endl;
	}


	return 0;
}
