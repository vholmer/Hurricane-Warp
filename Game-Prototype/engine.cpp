#include <iostream>

#include "engine.hpp"

using namespace std;

Engine::Engine() {
	this->parser = new Parser();
	this->roomHandler = new RoomHandler();
}

void Engine::memHandle() {
	delete this->parser;
	for(Player* p : this->players) {
		delete p;
	}
	for(Room* room : this->roomHandler->gameMap) {
		for(Item* item : room->itemsInRoom) {
			delete item;
		}
		for(Actor* actor : room->charsInRoom) {
			delete actor;
		}
		delete room;
	}
	delete this->roomHandler;
}

void Engine::printIntro() {
	cout << endl << "You have crashed on a mysterious planet!" << endl;
	cout << "In the name of the Emperor, good luck." << endl;
	cout << "What do you do?" << endl;
}

void Engine::tickActors() {
	for(Room* room : this->roomHandler->gameMap) {
		for(Actor* actor : room->charsInRoom) {
			actor->act();
		}
	}
}

void Engine::addPlayer() {
	Player* p = new Player();
	printIntro();
	p->currentRoom = this->roomHandler->start();
	p->roomInfo();
	this->players.push_back(p);
}

void Engine::startGameLoop() {
	bool gameOver = false;

	while(!gameOver) {
		for(Player* p : this->players) {
			gameOver = parser->processCommand(p, str);
		}
	}
}

void Engine::respawn() {
	cout << "No respawns lol" << endl;
}