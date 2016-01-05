#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <vector>

#include "room.hpp"
#include "player.hpp"
#include "item.hpp"

using namespace std;

struct Actor {

	Room* currentRoom;

	string name;
	string description;
	string dialogue;

	int health;

	vector<Item> inventory;

	virtual void act();

	virtual void walk();

	virtual void fight(Actor a);

	virtual void fight(Player p);

	virtual void pick_up(Item a);

	virtual void drop(Item a);

	virtual void talk_to(Actor a);

	virtual Player* playerInRoom();

	virtual Item* itemInRoom();
};

#endif