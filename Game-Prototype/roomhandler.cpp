#include "roomhandler.hpp"
#include "cultist.hpp"
#include "snilsson.hpp"
#include "daemon.hpp"

#include <iostream>

using namespace std;

struct Cultist;
struct Snilsson;

RoomHandler::RoomHandler() {
	// ----- ROOM INITIATIONS BEGIN -----

	Room* startRoom = new Room(string(
		"You are in a dark, twisted forest."
		));
	Room* cliff = new Room(string(
		"You are at the edge of a steep cliff, overlooking a warp-infested valley."
		));
	Room* cross = new Room(string("You are at a crossroads in the forest.\n")
		 + string("To the north, there is a warp-infested village.\n")
		 + string("To the west, there is a series of steep cliffs, overlooking the valley.\n")
		 + string("To the east you can see the mouth of a cave.\n")
		 + string("To the south there is a crashed ship. Possibly the one you came in.")
		);
	Room* cave = new Room(string("You are in a pitch-black cave. Something is lurking in the darkness..."));
	Room* abyss = new Room(string("The darkness creeps ever closer. Beware."));
	Room* crash = new Room(string("You are next to a huge cruiser wreckage.\n")
		+ string("Debris is is scattered everywhere."));
	Room* village = new Room(string("You are in a village plagued by warp storms."));
	Room* church = new Room(string("You are inside a huge cathedral.\n")
		+ string("A huge warp rift is humming at the end of the hall."));
	Room* warp = new Room(string(
		"You are in the middle of the warp itself, not even the emperor can save you."
		));

	Item* knife = new Item(string("A blade, simple but functional."),
		string("Knife"),
		5);
	Item* chainSword = new Item(string("A furiously deadly chain sword."),
		string("Chain-Sword"),
		20);
	Item* bolter = new Item(string("A standard issue heavy bolter."),
		string("Bolter"),
		15);
	Item* caffeine = new Item(string("A sealed jar of caffeine."),
		string("Caffeine"),
		1);

	cross->addItem(caffeine);
	abyss->addItem(bolter);
	cross->addItem(knife);
	crash->addItem(chainSword);

	startRoom->exits[EAST] = cliff;

	cliff->exits[WEST] = startRoom;
	cliff->exits[EAST] = cross;

	cross->exits[WEST] = cliff;
	cross->exits[SOUTH] = crash;
	cross->exits[EAST] = cave;
	cross->exits[NORTH] = village;

	crash->exits[NORTH] = cross;

	cave->exits[WEST] = cross;
	cave->exits[DOWN] = abyss;

	abyss->exits[UP] = cave;

	village->exits[SOUTH] = cross;
	village->exits[NORTH] = church;

	church->exits[SOUTH] = village;
	church->exits[NORTH] = warp;

	warp->exits[SOUTH] = church;

	this->gameMap.push_back(startRoom);
	this->gameMap.push_back(cliff);
	this->gameMap.push_back(cross);
	this->gameMap.push_back(crash);
	this->gameMap.push_back(cave);
	this->gameMap.push_back(abyss);
	this->gameMap.push_back(village);
	this->gameMap.push_back(church);
	this->gameMap.push_back(warp);

	// ----- ROOM INITIATIONS END -----

	// ----- ACTOR INITIATIONS BEGIN -----

	Cultist* cultist1 = new Cultist(string("Mal-Ek"),
		string("A cursed cultist, influenced by warp energies.")
		);

	Cultist* cultist2 = new Cultist(string("El-Rok"),
		string("A twisted cultist, consumed by chaos.")
		);

	Cultist* cultist3 = new Cultist(string("Malgor"),
		string("A psyker cultist, thirsting for blood.")
		);

	Snilsson* snilsson = new Snilsson(string("Sneel-Zon"),
		string("The chaos god himself.")
		);

	Daemon* demon = new Daemon(string("Daemon"),
		string("An abomination from the depths of the warp.")
		);

	cross->addChar(cultist1);
	cross->addChar(cultist2);
	cross->addChar(cultist3);
	warp->addChar(snilsson);
	abyss->addChar(demon);

	this->npcMap.push_back(cultist1);
	this->npcMap.push_back(cultist2);
	this->npcMap.push_back(cultist3);
	this->npcMap.push_back(snilsson);
	this->npcMap.push_back(demon);
	// ----- ACTOR INITIATIONS END -----
}

void RoomHandler::spawnDaemon(Engine* engine) {
	Daemon* demon = new Daemon(string("Daemon"),
	string("An abomination from the depths of the warp.")
	);
	this->gameMap[5]->addChar(demon);
	this->npcMap.push_back(demon);
	demon->globalBroadcast(engine, string("Daemon is alive!\n> "));
}

Room* RoomHandler::start() {
	return this->gameMap[0];
}