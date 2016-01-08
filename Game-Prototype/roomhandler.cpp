#include "roomhandler.hpp"
#include "cultist.hpp"
#include "snilsson.hpp"

#include <iostream>

using namespace std;

struct Cultist;
struct Snilsson;

RoomHandler::RoomHandler() {
	// ----- ROOM INITIATIONS BEGIN -----

	Room* startRoom = new Room(string(
		"You are in a dark, twisted forest."
		));
	Item* chainSword = new Item(string("A furiously deadly chain sword."),
		string("Chain-Sword")
		);

	Room* cliff = new Room(string(
		"You are at the edge of a steep cliff, overlooking a warp-infested valley."
		));
	Item* caffeine = new Item(string("A sealed jar of caffeine."),
		string("Caffeine")
		);

	Room* warp = new Room(string(
		"You are in the middle of the warp itself, not even the emperor can save you."
		));

	startRoom->addItem(chainSword);
	cliff->addItem(caffeine);

	startRoom->exits[EAST] = cliff;

	cliff->exits[WEST] = startRoom;
	cliff->exits[NORTH] = warp;

	warp->exits[SOUTH] = cliff;

	this->gameMap.push_back(startRoom);
	this->gameMap.push_back(cliff);
	this->gameMap.push_back(warp);

	// ----- ROOM INITIATIONS END -----

	// ----- ACTOR INITIATIONS BEGIN -----

	Cultist* cultist = new Cultist(string("Mal-Ek"),
		string("A cursed cultist, influenced by warp energies.")
		);

	Snilsson* snilsson = new Snilsson(string("Sneel-Zon"),
		string("The chaos god himself.")
		);

	cliff->addChar(cultist);
	warp->addChar(snilsson);

	this->npcMap.push_back(cultist);
	this->npcMap.push_back(snilsson);
	// ----- ACTOR INITIATIONS END -----
}

Room* RoomHandler::start() {
	return this->gameMap[0];
}