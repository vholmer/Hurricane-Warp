#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <iostream>

#include "item.hpp"
#include "roomhandler.hpp"

using namespace std;

struct Player {
	Room* currentRoom;
	vector<Item> inventory;
	int hitPoints;

	Player();

	Room* getRoomInDir(string dir);

	unordered_map<string, Room*> getExitMap();

	void roomInfo();
};

#endif