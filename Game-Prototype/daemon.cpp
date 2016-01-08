#include "daemon.hpp"

Daemon::Daemon(string name, string description) {
	this->name = name;
	this->description = description;

	this->health = 150;
	this->setDamageBase(4);
}

// Next level AI right here
void Daemon::act(Engine* engine) {
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