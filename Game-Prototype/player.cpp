#include "player.hpp"

string Player::getName() const {
	return this->name;
}

void Player::setName(string newName) {
	this->name = newName;
}

Room* Player::getRoom() {
	return this->currentRoom;
}

void Player::setRoom(Room* newRoom) {
	this->currentRoom = newRoom;
}

vector<Item*>& Player::getInventory() {
	return this->inventory;
}

int Player::getHealth() const {
	return this->health;
}

void Player::setHealth(int health) {
	this->health = health;
}

void Player::takeDamage(int toSubtract) {
	std::cerr << this << std::endl;
	this->health -= toSubtract;
}

int Player::getMaxHealth() const {
	return this->maxHealth;
}

int Player::getDamageBase() const {
	return this->damageBase;
}

bool Player::askedName() const {
	return this->askedForName;
}

void Player::setAskedName(bool askedForName) {
	this->askedForName = askedForName;
}

Player::Player() {
	this->maxHealth = 20;
	this->health = 20;
	this->askedForName = false;
	this->damageBase = 5;
}

Player::~Player() {
	std::cerr << "DESTROY EVERYTHING: " << this << std::endl;
}

Room* Player::getRoomInDir(string dir) {
	return this->currentRoom->exits[dir];
}

unordered_map<string, Room*> Player::getExitMap() {
	return this->currentRoom->exits;
}

void Player::broadcastDeath(Engine* engine) {
	for(Player* other : this->currentRoom->getPlayersInRoom()) {
		if(other != this) {
			ClientHandler* ch = engine->playerToClient[other];
			ch->sendMessage(string("\n" + this->name + " has died.\n> "));
		}
	}
}

string Player::printRoomDescription() {
	string retString;
	retString += this->currentRoom->getDescription() + "\n";
	return retString;
}

string Player::printActors() {
	string retString;
	for(Actor* actor : this->currentRoom->getCharsInRoom()) {
		retString += actor->getName() + " is here. ";
		retString += actor->getDescription() + "\n";
	}
	return retString;
}

string Player::printPlayers() {
	string retString;
	for(Player* p : this->currentRoom->getPlayersInRoom()) {
		if((p != this) && (p->name != ""))
			retString += p->name + " is here.\n";
	}
	return retString;
}

string Player::printItems() {
	string retString;
	retString += "Items in room: ";
	for(Item* item : this->currentRoom->getItemsInRoom()) {
		if(item != 0)
			retString += item->getName() + " ";
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

string Player::getInventoryString() {
	string retString;
	retString = "Inventory:\n";
	for(Item* item : this->inventory) {
		retString += item->getName() + " ";
	}
	if(retString.length() == 0) {
		retString = "You have nothing!";
	}
	retString += "\n> ";
	return retString;
}

int Player::fightPlayer(Player* p) {
	int damage = rand() % this->damageBase + this->getDamage();
	p->health -= damage;
	return damage;
}

int Player::fightActor(Actor* a) {
	int damage = rand() % this->damageBase + this->getDamage();
	a->takeDamage(damage);
	return damage;
}

void Player::addItem(Item* item, Engine* engine) {
	for(Item* inRoom : this->currentRoom->getItemsInRoom()) {
		if(item == inRoom) {
			this->inventory.push_back(inRoom);
			this->currentRoom->removeItem(inRoom);
			ClientHandler* ch = engine->playerToClient[this];
			ch->sendMessage(string("Added " + inRoom->getName() + " to inventory.\n> "));
			engine->broadcastItem(this, inRoom->getName(), true);
			return;
		}
	}
}

void Player::dropItem(Item* item, Engine* engine) {
	this->currentRoom->getItemsInRoom().push_back(item);
	for(auto i = this->inventory.begin(); i != this->inventory.end(); ++i) {
		if(*i == item) {
			this->inventory.erase(i);
			this->inventory.shrink_to_fit();
			break;
		}
	}
	ClientHandler* ch = engine->playerToClient[this];
	ch->sendMessage(string("\nDropped " + item->getName() + ".\n"));
	engine->broadcastItem(this, item->getName(), false);
}

void Player::dropAllItems(Engine* engine) {
	while(this->inventory.size() > 0) {
		for(Item* item : this->inventory) {
			this->dropItem(item, engine);
			break;
		}
	}
}

int Player::getDamage() {
	int totalDamage = this->damageBase;
	for(Item* item : this->inventory) {
		totalDamage += item->getDamage();
	}
	return totalDamage;
}

void Player::roomInfo(ClientHandler* ch) {
	string printString = this->printRoomDescription();
	printString += this->printActors();
	printString += this->printPlayers();
	printString += this->printItems();
	printString += this->printExits();
	ch->sendMessage(printString);
}