#ifndef ROOMHANDLER_HPP
#define ROOMHANDLER_HPP

#include <string>
#include <vector>

#include "room.hpp"

using namespace std;

struct Room;

struct RoomHandler {
	vector<Room*> gameMap;

	RoomHandler();

	Room* start();
};

#endif