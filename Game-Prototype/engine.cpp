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
	retString += "What do you do?\n\n";
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

void Engine::addPlayer(ClientHandler* c, string name) {
	Player* p = new Player();
	p->name = name;
	p->currentRoom = this->roomHandler->start();
	this->roomHandler->start()->addPlayer(p);
	c->sendMessage(this->printIntro());
	p->roomInfo(c);
	this->clientToPlayer[c] = p;
	this->playerToClient[p] = c;
}

void Engine::parseInput(ClientHandler* ch, string str) {
	globalMutex.lock();
	Player* p = this->clientToPlayer[ch];
	parser->processCommand(p, ch, str);
	globalMutex.unlock();
}

/*void Engine::startGameLoop() {
	bool gameOver = false;

	while(!gameOver) {
		for(pair<Player*, ClientHandler*> p : this->clients) {
			gameOver = this->parseInput(p.first, str);
		}
	}
}*/