#ifndef ROOMHANDLER_HPP
#define ROOMHANDLER_HPP

#include <string>
#include <vector>

#include "room.hpp"
#include "actor.hpp"

using namespace std;

struct Room;
struct Actor;

struct RoomHandler {
	vector<Room*> gameMap;
	vector<Actor*> npcMap;

	RoomHandler();

	Room* start();
};

#endif