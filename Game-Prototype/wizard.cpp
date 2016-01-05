#include "actor.hpp"

struct Wizard : public Actor {
	int mana;

	Wizard(string name, string description, Room* spawnRoom) {
		this->name = name;
		this->description = description;
		this->currentRoom = spawnRoom;

		this->dialogue = "I will curse you thoroughly!";

		this->health = 10;
		this->mana = 10;
	}

	// Next level AI right here
	virtual void act() {
		this->mana += 1;
		if(this->health < 3) {
			walk();
			return;
		}
		if(this->mana >= 3 && playerInRoom != 0) {
			enchant(playerInRoom());
			this->mana -= 3;
			return;
		} else if(playerInRoom != 0) {
			fight(playerInRoom());
			return;
		}
		walk();
	}

	virtual void walk() {
		auto possibleDirs = this->currentRoom->getExits();

		int diceRoll = rand() % possibleDirs.size();

		string chosenDir = possibleDirs[diceRoll];

		this->currentRoom->removeChar(this);

		Room* nextRoom = this->currentRoom->exits[chosenDir];

		this->currentRoom = nextRoom;


	}
};