#include "roomhandler.hpp"
#include "wizard.hpp"

#include <iostream>

using namespace std;

struct Wizard;

RoomHandler::RoomHandler() {
	// ----- ROOM INITIATIONS BEGIN -----

	Room* startRoom = new Room(1,
		string(
		"You are in a dark forest."
		));
	Item* knife = new Item(1,
		string("A very sharp knife."),
		string("Knife")
		);

	Room* clearing = new Room(2,
		string(
		"You are in a small clearing. There is a red house here."
		));
	Item* milk = new Item(2,
		string("A sealed jar of milk."),
		string("Milk")
		);

	startRoom->addItem(knife);
	startRoom->exits[EAST] = clearing;

	clearing->addItem(milk);
	clearing->exits[WEST] = startRoom;

	this->gameMap.push_back(startRoom);
	this->gameMap.push_back(clearing);

	// ----- ROOM INITIATIONS END -----

	// ----- ACTOR INITIATIONS BEGIN -----

	Wizard* wizard = new Wizard(1,
		string("Snilsson"),
		string("An evil wizard, breaking for-loops since 1984.")
		);

	clearing->addChar(wizard);

	// ----- ACTOR INITIATIONS END -----
}

Room* RoomHandler::start() {
	return this->gameMap[0];
}