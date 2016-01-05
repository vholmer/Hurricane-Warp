#include "room.hpp"

Room::Room(int id, string description) {
	this->roomID = id;
	this->description = description;
}

vector<string> getExits() {
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