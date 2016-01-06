#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <vector>

#include "room.hpp"
#include "player.hpp"
#include "item.hpp"

using namespace std;

struct Room;
struct Player;

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

	virtual void act() = 0;

	void walk(); //in actor.cpp

	void fight(Actor* a); //in actor.cpp

	void fight(Player* p); //in actor.cpp

	void pick_up(Item* a); //in actor.cpp

	void drop(Item* a); //in actor.cpp

	void talk(); //in actor.cpp

	Player* playerInRoom(); // in actor.cpp

	Item* itemInRoom(); // in actor.cpp
};

#endif