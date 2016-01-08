#include "snilsson.hpp"

Snilsson::Snilsson(string name, string description) {
	this->name = name;
	this->description = description;

	this->health = 200;
	this->setDamageBase(5);
}

// Next level AI right here
void Snilsson::act(Engine* engine) {
	Player* weakPlayer;
	if(weakPlayer != nullptr) {
		int damage = this->fight(weakPlayer);
		engine->broadcastPlayerDamage(this, weakPlayer, damage);
		return;
	}
}

Player* Snilsson::weakestPlayer() {
	Player* weakest = nullptr;
	bool firstIteration = true;
	for(Player* p : this->currentRoom->getPlayersInRoom()) {
		if(firstIteration) {
			weakest = p;
			firstIteration = false;
		}
		if(p->getHealth() <= weakest->getHealth()) {
			weakest = p;
		}
	}
	return weakest;
}

void Snilsson::die(Engine* engine) {
	engine->globalBroadcast(string(
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