#include "roomhandler.hpp"

#include <iostream>

using namespace std;

RoomHandler::RoomHandler() {
	// Initiate every single room
	gameMap.push_back(new Room(string("Welcome, padawan.")));
}

Room* RoomHandler::start() {
	return gameMap[0];
}