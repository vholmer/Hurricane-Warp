#include "wizard.hpp"

Wizard::Wizard(int id, string name, string description) {
	this->actorID = id;
	this->name = name;
	this->description = description;

	this->dialogue = "I will curse you thoroughly!";

	this->health = 10;
	this->mana = 10;
	this->setDamageBase(2);
}

// Next level AI right here
void Wizard::act() {
	this->mana += 1;
	if(this->health <= 0) {
		this->currentRoom->removeChar(this);
		delete this;
		return;
	}
	if(this->health < 3) {
		this->walk();
		return;
	}
	if(this->mana >= 5 && this->playerInRoom() != 0) {
		this->enchant(this->playerInRoom());
		this->mana -= 3;
		return;
	} else if(this->playerInRoom() != 0) {
		this->fight(this->playerInRoom());
		return;
	}
	this->walk();
}

void Wizard::enchant(Actor* a) {
	int damage = rand() % damageBase + 2;
	a->health -= damage;
}

void Wizard::enchant(Player* p) {
	int damage = rand() % damageBase + 2;
	p->health -= damage;
}