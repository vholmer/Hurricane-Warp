#include "actor.hpp"

struct Actor;
struct Player;

struct Wizard : public Actor {
	int mana;

	Wizard(string name, string description);

	virtual void act(Engine* engine) override;

	int enchant(Actor* a);

	int enchant(Player* p);
};