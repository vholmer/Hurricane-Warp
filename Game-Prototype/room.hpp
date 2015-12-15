#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "item.hpp"

using namespace std;

const string NORTH = "North";
const string EAST = "East";
const string SOUTH = "South";
const string WEST = "West";

struct Room {
	string description;
	vector<Item*> itemsInRoom;
	unordered_map<string, Room*> exits;
	//vector<Character> charsInRoom;
	Room(string description);

	void addItem(Item* item);

	void removeItem(Item* item);
};

#endif