#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <iostream>
#include <string>

#include "item.hpp"
#include "roomhandler.hpp"
#include "actor.hpp"
#include "engine.hpp"
#include "../Network-Prototype/clientHandler.hpp"

using namespace std;

struct Room;
struct ClientHandler;
struct Actor;
struct Engine;

struct Player {
	string name;
	Room* currentRoom;
	vector<Item*> inventory;
	int health;
	int damageBase;

	bool askedForName;

	Player();

	Room* getRoomInDir(string dir);

	unordered_map<string, Room*> getExitMap();

	void broadcastDeath(Engine* engine);

	string printRoomDescription();

	string printActors();

	string printPlayers();

	string printItems();

	string printExits();

	string printInventory();

	int fightPlayer(Player* p);

	int fightActor(Actor* a);

	void addItem(Item* item, Engine* engine);

	void dropItem(Item* item, Engine* engine);

	void dropAllItems(Engine* engine);

	void roomInfo(ClientHandler* ch);
};

#endif