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

const int GO = 1;
const int LOOK = 2;
const int HELP = 3;
const int QUIT = 4;

struct Parser {

	Player* player;

	unordered_map<string, int> commands;

	Parser(Player* player);

	void setUpCommands();

	vector<string> getInput();

	string toLowerCase(string str);

	bool processCommand();
};

#endif