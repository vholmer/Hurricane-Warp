#include "room.hpp"

Room::Room(string description) {
	this->description = description;
}

void Room::addItem(Item* item) {
	this->itemsInRoom.push_back(item);
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