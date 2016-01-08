#include "actor.hpp"

void Actor::setDamageBase(int damageBase) {
	this->damageBase = damageBase;
}

void Actor::die(Engine* engine) {
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

void Actor::walk(Engine* engine) {
	engine->broadcast(this, this->currentRoom, true);

	auto possibleDirs = this->currentRoom->getExits();

	int diceRoll = rand() % possibleDirs.size();

	string chosenDir = possibleDirs[diceRoll];

	Room* nextRoom = this->currentRoom->exits[chosenDir];

	Room* prevRoom = this->currentRoom;

	nextRoom->addChar(this);

	prevRoom->removeChar(this);

	if(this->playerInRoom() != 0) {
		this->printActor();
	}

	engine->broadcast(this, this->currentRoom, false);
}

void Actor::printActor() {
	cout << this->name << " is here. " << this->description << endl;
}

int Actor::fight(Actor* a) {
	int damage = rand() % this->damageBase + 1;
	a->health -= damage;
	return damage;
}

int Actor::fight(Player* p) {
	int damage = rand() % this->damageBase + 1;
	p->takeDamage(damage);
	return damage;
}

Player* Actor::playerInRoom() {
	if(this->currentRoom->getPlayersInRoom().size() > 0) {
		int randPlayer = rand() % this->currentRoom->getPlayersInRoom().size();
		return this->currentRoom->getPlayersInRoom()[randPlayer];
	}
	return nullptr;
}

Room* Actor::getRoom() {
	return this->currentRoom;
}

void Actor::setRoom(Room* newRoom) {
	this->currentRoom = newRoom;
}

string Actor::getName() const {
	return this->name;
}

string Actor::getDescription() const {
	return this->description;
}

void Actor::takeDamage(int toSubtract) {
	this->health -= toSubtract;
}

int Actor::getHealth() const {
	return this->health;
}