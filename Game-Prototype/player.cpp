#include "player.hpp"

Player::Player() {
	this->health = 10;
	this->askedForName = false;
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
	return retString;
}

string Player::printItems() {
	string retString;
	retString += "Items in room: ";
	for(Item* item : this->currentRoom->itemsInRoom) {
		if(item != 0)
			retString += item->name + " ";
	}
	retString += "\n";
	if(retString == "Items in room: \n")
		retString = "";
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

string Player::printInventory() {
	string retString;
	retString = "Inventory:\n";
	for(Item* item : this->inventory) {
		retString += item->name + " ";
	}
	if(retString.length() == 0) {
		retString = "You have nothing!";
	}
	retString += "\n> ";
	return retString;
}

void Player::addItem(Item* item) {
	for(Item* inRoom : this->currentRoom->itemsInRoom) {
		if(item == inRoom) {
			this->inventory.push_back(inRoom);
			this->currentRoom->removeItem(inRoom);
		}
	}
}

void Player::dropItem(Item* item) {
	this->currentRoom->itemsInRoom.push_back(item);
	for(auto i = this->inventory.begin(); i != this->inventory.end(); ++i) {
		if(*i == item) {
			this->inventory.erase(i);
			this->inventory.shrink_to_fit();
			return;
		}
	}
}

void Player::roomInfo(ClientHandler* ch) {
	string printString = this->printRoomDescription();
	printString += this->printActors();
	printString += this->printPlayers();
	printString += this->printItems();
	printString += this->printExits();
	ch->sendMessage(printString);
}