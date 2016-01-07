#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <locale>
#include <functional>

#include "player.hpp"
#include "../Network-Prototype/clientHandler.hpp"

using namespace std;

struct Player;
struct ClientHandler;

struct Parser {

	enum class cmd : int {
		GO = 1,
		LOOK,
		HELP,
		INVENTORY
	};

	Player* player;

	map<cmd, std::function<void(string)> > funcMap;

	unordered_map<string, cmd> commands;

	Parser();

	void setUpLambdas(Player* p, ClientHandler* ch);

	void setUpCommands();

	vector<string> getInput(string str);

	string toLowerCase(string str);

	void processCommand(Player* p, ClientHandler* ch, string str);
};

#endif