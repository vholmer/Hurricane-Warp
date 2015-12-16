#include "player.hpp"

Player::Player() {
	this->hitPoints = 10;
}

Room* Player::getExits(string dir) {
	return this->currentRoom->exits[dir];
}

void Player::roomInfo() {
	cout << endl << this->currentRoom->description << endl;
	cout << "Items in room: ";
	for(Item* item : this->currentRoom->itemsInRoom) {
		cout << item->name << " ";
	}
	cout << endl;
	cout << "Exits: ";
	for(pair<string, Room*> p : this->currentRoom->exits) {
		cout << p.first << " ";
	}
	cout << endl;
}