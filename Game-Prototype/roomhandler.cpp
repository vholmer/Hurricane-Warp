#include "roomhandler.hpp"

#include <iostream>

using namespace std;

RoomHandler::RoomHandler() {
	// This method will initiate all rooms
	// How to initiate a room:

	Room* startRoom = new Room(string(
		"You are in a dark forest."
		));
	Item* knife = new Item(
		string("A very sharp knife."),
		string("Knife")
		);

	Room* clearing = new Room(string(
		"You are in a small clearing. There is a red house here."
		));
	Item* milk = new Item(
		string("A sealed jar of milk."),
		string("Milk")
		);

	startRoom->addItem(knife);
	startRoom->exits[EAST] = clearing;
	this->gameMap.push_back(startRoom);

	clearing->addItem(milk);
	clearing->exits[WEST] = startRoom;
	this->gameMap.push_back(clearing);
}

Room* RoomHandler::start() {
	return this->gameMap[1];
}