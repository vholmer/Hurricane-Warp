#include "room.hpp"

Room::Room(string description) {
	this->description = description;
}

void Room::addItem(Item* item) {
	this->itemsInRoom.push_back(item);
}