#include<iostream>

#include "../header/token/Base.hpp"
#include "../header/Parser.hpp"

using namespace std;


int main(){

	int num = 1;
	for(int i = 0; i < num; ++i){
		cout << "$ ";
		string cmdLine;
		getline(cin,cmdLine);

		Parser* parserObj = new Parser(cmdLine);
		parserObj->parse();
		Base* compObj = parserObj->parse();
		if(compObj != nullptr){
			cout << endl << "--DISPLAY--" << endl;
			cout << compObj->stringify();
			cout << endl << "--EXECUTE--" << endl;
			compObj->execute();
		}

	}

}