#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <locale>

#include "player.hpp"

using namespace std;

struct Parser {

	enum class cmd : int {
		GO = 1,
		LOOK,
		HELP,
		QUIT
	};

	Player* player;

	unordered_map<string, cmd> commands;

	Parser(Player* player);

	void setUpCommands();

	vector<string> getInput();

	string toLowerCase(string str);

	bool processCommand();
};

#endif