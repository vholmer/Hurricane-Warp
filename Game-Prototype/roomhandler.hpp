#ifndef ROOMHANDLER_HPP
#define ROOMHANDLER_HPP

#include <string>
#include <vector>

#include "room.hpp"
#include "actor.hpp"

using namespace std;

struct Room;
struct Actor;
struct Engine;

struct RoomHandler {
	vector<Room*> gameMap;
	vector<Actor*> npcMap;

	RoomHandler();

	Room* start();

	void spawnDaemon(Engine* engine);
};

#endif