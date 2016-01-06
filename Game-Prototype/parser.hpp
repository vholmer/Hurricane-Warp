#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <locale>

#include "player.hpp"

using namespace std;

struct Player;

struct Parser {

	enum class cmd : int {
		GO = 1,
		LOOK,
		HELP,
		QUIT,
		INVENTORY
	};

	Player* player;

	map<cmd, std::function<bool(string)> > funcMap;

	unordered_map<string, cmd> commands;

	Parser(Player* player);

	void setUpLambdas();

	void setUpCommands();

	vector<string> getInput();

	string toLowerCase(string str);

	bool processCommand();
};

#endif