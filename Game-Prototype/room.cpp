#include "room.hpp"

Room::Room(string description) {
	this->description = description;
}

string Room::getDescription() const {
	return this->description;
}

vector<Item*>& Room::getItemsInRoom() {
	return this->itemsInRoom;
}

vector<Actor*>& Room::getCharsInRoom() {
	return this->charsInRoom;
}

vector<Player*>& Room::getPlayersInRoom() {
	return this->playersInRoom;
}

vector<string> Room::getExits() {
	vector<string> exits;
	for(pair<string, Room*> p : this->exits) {
		if(p.second != 0)
			exits.push_back(p.first);
	}
	return exits;
}

void Room::addItem(Item* item) {
	this->itemsInRoom.push_back(item);
}

void Room::addChar(Actor* actor) {
	this->charsInRoom.push_back(actor);
	actor->setRoom(this);
}

void Room::addPlayer(Player* p) {
	this->playersInRoom.push_back(p);
	p->setRoom(this);
}

void Room::removeItem(Item* item) {
	for(auto i = this->itemsInRoom.begin(); i != this->itemsInRoom.end(); ++i) {
		if(*i == item) {
			this->itemsInRoom.erase(i);
			this->itemsInRoom.shrink_to_fit();
			return;
		}
	}
}

void Room::removeChar(Actor* actor) {
	for(auto i = this->charsInRoom.begin(); i != this->charsInRoom.end(); ++i) {
		if(*i == actor) {
			this->charsInRoom.erase(i);
			this->charsInRoom.shrink_to_fit();
			return;
		}
	}
}

void Room::removePlayer(Player* p) {
	for(auto i = this->playersInRoom.begin(); i != this->playersInRoom.end(); ++i) {
		if(*i == p) {
			this->playersInRoom.erase(i);
			this->playersInRoom.shrink_to_fit();
			return;
		}
	}
}