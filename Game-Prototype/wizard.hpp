#include "actor.hpp"

struct Actor;
struct Player;

struct Wizard : public Actor {
	int mana;

	Wizard(string name, string description, Room* spawnRoom);

	virtual void act();

	void enchant(Actor* a);

	void enchant(Player* p);
};