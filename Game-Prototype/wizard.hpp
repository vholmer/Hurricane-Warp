#include "actor.hpp"

struct Actor;
struct Player;

struct Wizard : public Actor {
	int mana;

	Wizard(string name, string description);

	virtual void act() override;

	void enchant(Actor* a);

	void enchant(Player* p);
};