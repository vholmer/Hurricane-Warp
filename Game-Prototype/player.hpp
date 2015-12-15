#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "item.hpp"
#include "roomhandler.hpp"

using namespace std;

struct Player {
	Room* currentRoom;
	vector<Item> inventory;
	int hitPoints;

	Player();
};

#endif