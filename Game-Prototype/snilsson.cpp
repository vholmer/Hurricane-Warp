#include "snilsson.hpp"

Snilsson::Snilsson(string name, string description) {
	this->name = name;
	this->description = description;

	this->dialogue = "The Chaos gods are thirsty...your blood will do!";

	this->health = 200;
	this->setDamageBase(5);
}

// Next level AI right here
void Snilsson::act(Engine* engine) {
	Player* weakPlayer = this->weakestPlayer();
	if(weakPlayer != 0) {
		int damage = this->fight(weakPlayer);
		this->broadcastPlayerDamage(engine, weakPlayer, damage);
		return;
	}
}

Player* Snilsson::weakestPlayer() {
	Player* weakest;
	bool firstIteration = true;
	for(Player* p : this->currentRoom->playersInRoom) {
		if(firstIteration) {
			weakest = p;
			firstIteration = false;
		}
		if(p->health <= weakest->health) {
			weakest = p;
		}
	}
	return weakest;
}

void Snilsson::die(Engine* engine) {
	this->globalBroadcast(engine, string(
		"The chaos god " + this->name + " has died!\n"
		+ "By the Emperor, these lands are safe.\n> "
		));
	this->currentRoom->removeChar(this);
	auto begin = engine->roomHandler->npcMap.begin();
	auto end = engine->roomHandler->npcMap.end();
	for(auto i = begin; i != end; ++i) {
		if(*i == this) {
			engine->roomHandler->npcMap.erase(i);
			return;
		}
	}
}