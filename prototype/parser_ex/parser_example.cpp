#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/metaparse/entire_input.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/phoenix.hpp>

using namespace std;
using namespace boost;

int main(){

	namespace qi = boost::spirit::qi;
	/*
	template <typename Iterator>
	struct parser : qi::grammar<Iterator> {
		typedef parser_skipper<Iterator> Skipper;
		parser() : parser::base_type(command)
		{
			using namespace qi;
			
			command = "ls" ;
			arg = "arg" ;
			flag = "-";
			connector = "&&" ;

		}
	
		qi::rule<Iterator, Skipper> command;
		qi::rule<Iterator, Skipper> arg;
		qi::rule<Iterator, Skipper> flag;
		qi::rule<Iterator, Skipper> connector;
	};*/
	
	string input;

	cout << "Input a line: \n";

	getline(cin, input);
	cout << "Got " << input << " \n";

	unsigned count = 0;

	tokenizer<> tok(input);

	for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
		cout << *beg << "\n";
	}


	return 0;
}
