#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <vector>

#include "room.hpp"
#include "player.hpp"
#include "item.hpp"
#include "engine.hpp"
#include "../Network-Prototype/clientHandler.hpp"

using namespace std;

struct Room;
struct Player;
struct Engine;
struct ClientHandler;

struct Actor {

	Room* currentRoom;

	string name;
	string description;
	string dialogue;

	int actorID;
	int health;
	int damageBase;

	vector<Item*> inventory;

	void setDamageBase(int damageBase); //in actor.cpp

	virtual ~Actor() = default;

	virtual void act(Engine* engine) = 0;

	void broadcast(Engine* engine, Room* prevRoom, bool leftRoom);

	void walk(Engine* engine); //in actor.cpp

	void printActor();

	void fight(Actor* a); //in actor.cpp

	void fight(Player* p); //in actor.cpp

	void pick_up(Item* a); //in actor.cpp

	void drop(Item* a); //in actor.cpp

	void talk(); //in actor.cpp

	Player* playerInRoom(); // in actor.cpp

	Item* itemInRoom(); // in actor.cpp
};

#endif