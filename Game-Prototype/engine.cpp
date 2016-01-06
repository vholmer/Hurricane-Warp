#include <iostream>
#include <mutex>

#include "engine.hpp"

using namespace std;

mutex globalMutex;

Engine::Engine() {
	this->parser = new Parser();
	this->roomHandler = new RoomHandler();
}

void Engine::memHandle() {
	delete this->parser;
	for(pair<Player*, ClientHandler*> p : this->playerToClient) {
		delete p.first;
		delete p.second;
	}
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

void Engine::killConnections() {
	for(pair<Player*, ClientHandler*> p : this->playerToClient) {
		p.second->quitConnection();
	}
}

void Engine::printIntro() {
	cout << endl << "You have crashed on a mysterious planet!" << endl;
	cout << "In the name of the Emperor, good luck." << endl;
	cout << "What do you do?" << endl;
}

void Engine::tickActors() {
	globalMutex.lock();
	for(Room* room : this->roomHandler->gameMap) {
		for(Actor* actor : room->charsInRoom) {
			actor->act();
		}
	}
	globalMutex.unlock();
}

void Engine::addPlayer(ClientHandler* ch) {
	Player* p = new Player();
	p->currentRoom = this->roomHandler->start();
	this->clientToPlayer[p] = ch;
	this->playerToClient[ch] = p;
}

bool Engine::parseInput(ClientHandler* ch, string str) {
	globalMutex.lock();
	Player* p = this->clientToPlayer[ch];
	bool retBool = parser->processCommand(p, str);
	globalMutex.unlock();
	return retBool;
}

void Engine::startGameLoop() {
	bool gameOver = false;

	while(!gameOver) {
		for(pair<Player*, ClientHandler*> p : this->clients) {
			gameOver = this->parseInput(p.first, str);
		}
	}
}

void Engine::respawn() {
	cout << "No respawns lol" << endl;
}