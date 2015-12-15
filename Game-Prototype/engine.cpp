#include <iostream>

#include "engine.hpp"

using namespace std;

Engine::Engine() {
	this->player = new Player();
	this->parser = new Parser(this->player);
	this->roomHandler = new RoomHandler();
}

void Engine::memHandle() {
	delete this->parser;
	delete this->player;
	for(Room* room : this->roomHandler->gameMap) {
		for(Item* item : room->itemsInRoom) {
			delete item;
		}
		delete room;
	}
	delete this->roomHandler;
}

void Engine::printIntro() {
	cout << "You have crashed on a mysterious planet!" << endl;
	cout << "In the name of the Emperor, good luck." << endl;
	cout << "What do you do?" << endl << endl;
}

void Engine::startGameLoop() {
	//TODO: make this a lot less complicated, especially room / item descr.
	printIntro();
	this->player->currentRoom = this->roomHandler->start();
	
	/*
	cout << this->player->currentRoom->description << endl;
	cout << "Items in room: ";
	for(Item* item : this->player->currentRoom->itemsInRoom) {
		cout << item->name << " ";
	}
	cout << endl;
	cout << "Exits: ";
	for(pair<string, Room*> p : this->player->currentRoom->exits) {
		cout << p.first << " ";
	}
	cout << endl;
	*/

	bool gameOver = false;

	while(!gameOver) {
		gameOver = parser->processCommand();
	}
}

void Engine::respawn() {
	cout << "No respawns lol" << endl;
}