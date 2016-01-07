#include "engine.hpp"

using namespace std;

mutex globalMutex;
mutex deleteMutex;

Engine::Engine() {
	this->parser = new Parser();
	this->roomHandler = new RoomHandler();
	this->spin = true;
	this->managerThread = async(std::launch::async, &Engine::clientManager, this);
}

void Engine::clientManager() {
	while(this->spin) {
		usleep(100000);
		for(pair<Player*, ClientHandler*> p : this->playerToClient) {
			if(p.second->objectDead) {
				deleteClient(p.first, p.second);
				this->playerToClient.erase(p.first);
				this->clientToPlayer.erase(p.second);
			}
			break;
		}
	}
}

void Engine::deleteClient(Player* p, ClientHandler* ch) {
	deleteMutex.lock();
	p->currentRoom->removePlayer(p);
	delete ch;
	delete p;
	deleteMutex.unlock();
}

void Engine::memHandle() {
	this->spin = false;
	this->managerThread.wait();
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
	if(p->askedForName == false) {
		c->sendMessage(string("What is your name?\n> "));
	}
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