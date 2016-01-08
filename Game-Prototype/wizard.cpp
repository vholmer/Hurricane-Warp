#include "wizard.hpp"

Wizard::Wizard(string name, string description) {
	this->name = name;
	this->description = description;

	this->dialogue = "I will curse you thoroughly!";

	this->health = 10;
	this->mana = 10;
	this->setDamageBase(2);
}

// Next level AI right here
void Wizard::act(Engine* engine) {
	this->mana += 1;
	Player* randomPlayer = this->playerInRoom();
	if(this->health < 3) {
		this->walk(engine);
		return;
	}
	if(randomPlayer != 0) {
		int damage = this->fight(randomPlayer);
		this->broadcastPlayerDamage(engine, randomPlayer, damage);
		return;
	}
	this->walk(engine);
}