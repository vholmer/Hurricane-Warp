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
	if(this->health <= 0) {
		this->currentRoom->removeChar(this);
		auto begin = engine->roomHandler->npcMap.begin();
		auto end = engine->roomHandler->npcMap.end();
		for(auto i = begin; i != end; ++i) {
			if(*i == this) {
				engine->roomHandler->npcMap.erase(i);
				engine->roomHandler->npcMap.shrink_to_fit();
			}
		}
		delete this;
		return;
	}
	if(this->health < 3) {
		this->walk(engine);
		return;
	}
	if(this->mana >= 5 && randomPlayer != 0) {
		this->enchant(randomPlayer);
		this->mana -= 3;
		engine->checkHealth(randomPlayer, engine->playerToClient[randomPlayer]);
		return;
	} else if(randomPlayer != 0) {
		this->fight(randomPlayer);
		engine->checkHealth(randomPlayer, engine->playerToClient[randomPlayer]);
		return;
	}
	this->walk(engine);
}

void Wizard::enchant(Actor* a) {
	int damage = rand() % damageBase + 2;
	a->health -= damage;
}

void Wizard::enchant(Player* p) {
	int damage = rand() % damageBase + 2;
	p->health -= damage;
}