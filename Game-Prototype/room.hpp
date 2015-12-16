#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "item.hpp"

using namespace std;

const string NORTH = "north";
const string EAST = "east";
const string SOUTH = "south";
const string WEST = "west";

struct Room {
	int roomID;
	string description;
	vector<Item*> itemsInRoom;
	unordered_map<string, Room*> exits;
	//vector<Character> charsInRoom;
	Room(int id, string description);

	void addItem(Item* item);

	void removeItem(Item* item);
};

#endif
