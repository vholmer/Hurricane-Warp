#include "daemon.hpp"

Daemon::Daemon(string name, string description) {
	this->name = name;
	this->description = description;

	this->dialogue = "The Chaos gods are thirsty...your blood will do!";

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
	if(randomPlayer != 0) {
		int damage = this->fight(randomPlayer);
		this->broadcastPlayerDamage(engine, randomPlayer, damage);
		return;
	}
	this->walk(engine);
}