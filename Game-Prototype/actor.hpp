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

	bool markedForDeath = false;

	vector<Item*> inventory;

	void setDamageBase(int damageBase); //in actor.cpp

	virtual ~Actor() = default;

	virtual void act(Engine* engine) = 0;

	void die(Engine* engine);

	void broadcast(Engine* engine, Room* prevRoom, bool leftRoom);

	void broadcastPlayerDamage(Engine* engine, Player* p, int dmg);

	void broadcastActorDamage(Engine* engine, Actor* actor, int dmg);

	void walk(Engine* engine); //in actor.cpp

	void printActor();

	int fight(Actor* a); //in actor.cpp

	int fight(Player* p); //in actor.cpp

	void pick_up(Item* a); //in actor.cpp

	void drop(Item* a); //in actor.cpp

	void talk(); //in actor.cpp

	Player* playerInRoom(); // in actor.cpp

	Item* itemInRoom(); // in actor.cpp
};

#endif