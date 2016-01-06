#include "player.hpp"

Player::Player() {
	this->health = 10;
}

Room* Player::getRoomInDir(string dir) {
	return this->currentRoom->exits[dir];
}

unordered_map<string, Room*> Player::getExitMap() {
	return this->currentRoom->exits;
}

void Player::printRoomDescription() {
	cout << endl << this->currentRoom->description << endl;
}

void Player::printActors() {
	for(Actor* actor : this->currentRoom->charsInRoom) {
		cout << actor->name << " is here. " << actor->description << endl;
	}
}

void Player::printItems() {
	cout << "Items in room: ";
	for(Item* item : this->currentRoom->itemsInRoom) {
		cout << item->name << " ";
	}
	cout << endl;
}

void Player::printExits() {
	cout << "Exits: ";
	for(string s : this->currentRoom->getExits()) {
		cout << s << " ";
	}
	cout << endl;
}

void Player::roomInfo() {
	this->printRoomDescription();
	this->printActors();
	this->printItems();
	this->printExits();
}