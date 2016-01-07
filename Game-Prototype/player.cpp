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

string Player::printRoomDescription() {
	string retString;
	retString += this->currentRoom->description + "\n";
	return retString;
}

string Player::printActors() {
	string retString;
	for(Actor* actor : this->currentRoom->charsInRoom) {
		retString += actor->name + " is here. ";
		retString += actor->description + "\n";
	}
	return retString;
}

string Player::printPlayers() {
	string retString;
	for(Player* p : this->currentRoom->playersInRoom) {
		if(p != this)
			retString += p->name + " is here.\n";
	}
	if(retString.length() > 2)
		retString += "\n";
	return retString;
}

string Player::printItems() {
	string retString;
	retString += "Items in room: ";
	for(Item* item : this->currentRoom->itemsInRoom) {
		retString += item->name + " ";
	}
	if(retString.length() > 2)
		retString += "\n";
	return retString;
}

string Player::printExits() {
	string retString;
	retString += "Exits: ";
	for(string s : this->currentRoom->getExits()) {
		retString += s + " ";
	}
	retString += "\n> ";
	return retString;
}

void Player::roomInfo(ClientHandler* ch) {
	string printString = this->printRoomDescription();
	printString += this->printActors();
	printString += this->printPlayers();
	printString += this->printItems();
	printString += this->printExits();
	ch->sendMessage(printString);
}