#include "wizard.hpp"

Wizard::Wizard(string name, string description, Room* spawnRoom) {
	this->name = name;
	this->description = description;
	this->currentRoom = spawnRoom;

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
		walk();
		return;
	}
	if(this->mana >= 5 && playerInRoom() != 0) {
		enchant(playerInRoom());
		this->mana -= 3;
		return;
	} else if(playerInRoom() != 0) {
		fight(playerInRoom());
		return;
	}
	walk();
}

void Wizard::enchant(Actor* a) {
	int damage = rand() % damageBase + 2;
	a->health -= damage;
}

void Wizard::enchant(Player* p) {
	int damage = rand() % damageBase + 2;
	p->health -= damage;
}