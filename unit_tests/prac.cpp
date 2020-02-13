#include <iostream>
#include <string>
// #include "../header/token/Command.hpp"
#include "../header/Parser.hpp"

using namespace std;

int main(){

	/*
	int num = 1;
	for(int i = 0; i < num; ++i){
		cout << "$ ";
		string cmdLine;
		getline(cin,cmdLine);

		Parser* parserObj = new Parser(cmdLine);
		parserObj->parse();
		// Base* compObj = parserObj->parse();
		// if(compObj != nullptr){
		// 	cout << endl << "--DISPLAY--" << endl;
		// 	cout << compObj->stringify();
		// 	cout << endl << "--EXECUTE--" << endl;
		// 	compObj->execute();
		// }
	}*/

	Parser* test = new Parser("ls -a && git status || eat ass");
    Base* cmd1 = new Command({"ls", "-a"});
    Base* ctr1 = new And();
    Base* cmd2 = new Command({"git", "status"});
    Base* ctr2 = new Or();

    /* set up first base* for comparison */
    //Base* squashed1 = new And(cmd1, cmd2);


    /* set up second base* for comparison */
    vector<Base*> baseList;
    baseList.push_back(cmd1);
    baseList.push_back(ctr1);
    baseList.push_back(cmd2);
    baseList.push_back(ctr2);
    baseList.push_back(cmd3);

    Base* squashed2 = test->getSquashed(baseList);

    cout << squashed2->stringify();


	return 0;
}
