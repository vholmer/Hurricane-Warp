#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

using namespace std;

struct Parser {
	enum word {
		GO = 0,
		LOOK,
		HELP,
		SAY
	};

	string command[4] = {"go", "look", "help", "say"};

	string getCommand();
};

#endif