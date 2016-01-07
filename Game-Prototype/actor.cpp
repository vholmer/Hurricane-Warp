#include "actor.hpp"

void Actor::setDamageBase(int damageBase) {
	this->damageBase = damageBase;
}

void Actor::broadcast(Engine* engine, Room* room, bool leftRoom) {
	for(Player* p : room->playersInRoom) {
		ClientHandler* ch = engine->playerToClient[p];
		if(leftRoom)
			ch->sendMessage(string("\n" + this->name + " has left the room.\n> "));
		else
			ch->sendMessage(string("\n" + this->name + " has entered the room.\n> "));
	}
}

void Actor::walk(Engine* engine) {
	broadcast(engine, this->currentRoom, true);

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

	broadcast(engine, this->currentRoom, false);
}

void Actor::printActor() {
	cout << this->name << " is here. " << this->description << endl;
}

void Actor::fight(Actor* a) {
	int damage = rand() % damageBase + 1;
	a->health -= damage;
}

void Actor::fight(Player* p) {
	int damage = rand() % damageBase + 1;
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