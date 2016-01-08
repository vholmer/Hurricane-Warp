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
#include "engine.hpp"
#include "room.hpp"
#include "../Network-Prototype/clientHandler.hpp"

using namespace std;

struct Player;
struct ClientHandler;
struct Engine;
struct Room;

struct Parser {

	enum class cmd : int {
		GO = 1,
		LOOK,
		HELP,
		INVENTORY,
		TAKE,
		DROP,
		FIGHT,
		EXAMINE
	};

	map<cmd, std::function<void(string)> > funcMap;

	unordered_map<string, cmd> commands;

	Engine* engine;

	Parser(Engine* engine);

	void setUpLambdas(Player* p, ClientHandler* ch);

	void setUpCommands();

	vector<string> getInput(string str);

	string toLowerCase(string str);

	string printIntro();

	void broadcastMovement(Player* p, Room* prevRoom);

	void broadcastItem(Player* p, string itemName, bool pickedUp);

	void processCommand(Player* p, ClientHandler* ch, string str);
};

#endif