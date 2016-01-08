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

private:
	string name;
	Room* currentRoom;
	vector<Item*> inventory;
	int health;
	int maxHealth;
	int damageBase;

	bool askedForName;

public:

	Player();

	~Player();

	string getName() const;

	void setName(string newName);

	Room* getRoom();

	void setRoom(Room* newRoom);

	vector<Item*>& getInventory();

	int getHealth() const;

	void setHealth(int health);

	void takeDamage(int toSubtract);

	int getMaxHealth() const;

	int getDamageBase() const;

	bool askedName() const;

	void setAskedName(bool askedForName);

	void dropAllItems(Engine* engine);

	void broadcastDeath(Engine* engine);

	void roomInfo(ClientHandler* ch);

	unordered_map<string, Room*> getExitMap();

	Room* getRoomInDir(string dir);

	string getInventoryString();

	void addItem(Item* item, Engine* engine);

	void dropItem(Item* item, Engine* engine);

	int fightPlayer(Player* p);

	int fightActor(Actor* a);

private:

	string printRoomDescription();

	string printActors();

	string printPlayers();

	string printItems();

	string printExits();

	int getDamage();
};

#endif