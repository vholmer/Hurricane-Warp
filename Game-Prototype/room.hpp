#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

#include "item.hpp"

using namespace std;

struct Room {
	string description;
	vector<Item> itemsInRoom;
	//vector<Character> charsInRoom;
	Room(string description);
};

#endif