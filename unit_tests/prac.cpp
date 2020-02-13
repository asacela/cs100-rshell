#include <iostream>
#include <string>
// #include "../header/token/Command.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	int num = 1;
	for(int i = 0; i < num; ++i){
		cout << "$ ";
		string cmdLine;
		getline(cin,cmdLine);

		Parser* parserObj = new Parser(cmdLine);
		Base* compObj = parserObj->parse();
		if(compObj != nullptr){
			cout << endl << "--DISPLAY--" << endl;
			compObj->display();
			cout << endl << "--EXECUTE--" << endl;
			compObj->execute();

		}

	}

	return 0;
}
