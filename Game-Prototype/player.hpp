#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <iostream>
#include <string>

#include "item.hpp"
#include "roomhandler.hpp"
#include "../Network-Prototype/clientHandler.hpp"

using namespace std;

struct Room;
struct ClientHandler;

struct Player {
	string name;
	Room* currentRoom;
	vector<Item> inventory;
	int health;

	Player();

	Room* getRoomInDir(string dir);

	unordered_map<string, Room*> getExitMap();

	string printRoomDescription();

	string printActors();

	string printPlayers();

	string printItems();

	string printExits();

	void roomInfo(ClientHandler* ch);
};

#endif