#include "cultist.hpp"

Cultist::Cultist(string name, string description) {
	this->name = name;
	this->description = description;

	this->health = 10;
	this->setDamageBase(2);
}

// Next level AI right here
void Cultist::act(Engine* engine) {
	Player* randomPlayer = this->playerInRoom();
	if(this->health < 3) {
		this->walk(engine);
		return;
	}
	if(randomPlayer != nullptr) {
		int damage = this->fight(randomPlayer);
		engine->broadcastPlayerDamage(this, randomPlayer, damage);
		return;
	}
	this->walk(engine);
}