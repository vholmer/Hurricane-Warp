#include <iostream>
#include <mutex>
#include <unordered_map>

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

string Engine::printIntro() {
	string retString;
	retString += "\nYou have crashed on a mysterious planet!\n";
	retString += "In the name of the Emperor, good luck.\n";
	retString += "What do you do?\n";
	return retString;
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

void Engine::addPlayer(ClientHandler* c) {
	Player* p = new Player();
	p->currentRoom = this->roomHandler->start();
	c->sendMessage(this->printIntro());
	this->clientToPlayer[c] = p;
	this->playerToClient[p] = c;
}

bool Engine::parseInput(ClientHandler* ch, string str) {
	globalMutex.lock();
	Player* p = this->clientToPlayer[ch];
	bool retBool = parser->processCommand(p, str);
	globalMutex.unlock();
	return retBool;
}

/*void Engine::startGameLoop() {
	bool gameOver = false;

	while(!gameOver) {
		for(pair<Player*, ClientHandler*> p : this->clients) {
			gameOver = this->parseInput(p.first, str);
		}
	}
}*/

void Engine::respawn() {
	cout << "No respawns lol" << endl;
}