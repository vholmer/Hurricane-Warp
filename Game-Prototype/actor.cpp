#include "actor.hpp"

void Actor::setDamageBase(int damageBase) {
	this->damageBase = damageBase;
}

void Actor::walk() {
	auto possibleDirs = this->currentRoom->getExits();

	int diceRoll = rand() % possibleDirs.size();

	string chosenDir = possibleDirs[diceRoll];

	this->currentRoom->removeChar(this);

	Room* nextRoom = this->currentRoom->exits[chosenDir];

	this->currentRoom = nextRoom;
}

void Actor::fight(Actor* a) {
	int damage = rand() % damageBase;
	a->health -= damage;
}

void Actor::fight(Player* p) {
	int damage = rand() % damageBase;
	p->health -= damage;
}

void Actor::pick_up(Item* a) {
	this->inventory.push_back(a);
	this->currentRoom->removeItem(a);
}

void Actor::drop(Item* a) {
	for(auto i = this->inventory.begin(); i != this->inventory.end(); ++i) {
		if(*i == a) {
			this->currentRoom->addItem(a);
			this->inventory.erase(i);
			this->inventory.shrink_to_fit();
		}
	}
}

void Actor::talk() {
	if(this->playerInRoom() != 0) {
		cout << this->dialogue << endl;
	}
}

Player* Actor::playerInRoom() {
	if(this->currentRoom->playersInRoom.size() > 0) {
		int randPlayer = rand() % this->currentRoom->playersInRoom.size();
		return this->currentRoom->playersInRoom[randPlayer];
	}
	return (Player*) 0;
}