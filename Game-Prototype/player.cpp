#include "player.hpp"

Player::Player() {
	this->hitPoints = 10;
}

Room* Player::getRoomInDir(string dir) {
	return this->currentRoom->exits[dir];
}

unordered_map<string, Room*> Player::getExitMap() {
	return this->currentRoom->exits;
}

void Player::roomInfo() {
	cout << endl << this->currentRoom->description << endl;
	cout << "Items in room: ";
	for(Item* item : this->currentRoom->itemsInRoom) {
		cout << item->name << " ";
	}
	cout << endl;
	cout << "Exits: ";
	cout << this->currentRoom->getExits();
	cout << endl;
}