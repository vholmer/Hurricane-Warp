#include "engine.hpp"

using namespace std;

mutex globalMutex;
mutex checkMutex;

Engine::Engine() {
	this->parser = new Parser(this);
	this->roomHandler = new RoomHandler();
	this->spin = true;
	this->tickThread = async(std::launch::async, &Engine::tickActors, this);

}

void Engine::memHandle() {
	this->spin = false;
	this->tickThread.wait();

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

	cout.flush();
}

void Engine::killConnections() {
	for(pair<Player*, ClientHandler*> p : this->playerToClient) {
		p.second->quitConnection();
	}
}

void Engine::tickActors() {
	cout << "1" << endl;
	while(this->spin) {
		cout << "2" << endl;
		int sleepSeconds = (rand() % 7) + 6;
		cout << "3" << endl;
		usleep(sleepSeconds * 1000 * 1000);
		cout << "4" << endl;
		checkMutex.lock();
		cout << "5" << endl;
		for(Actor* actor : this->roomHandler->npcMap) {
			cout << "ACTLOOP 1" << endl;
			actor->act(this);
			cout << "ACTLOOP 2" << endl;
		}
		checkMutex.unlock();
		cout << "6" << endl;
		this->checkActorHealth();
		cout << "7" << endl;
		this->checkPlayerHealth();
		cout << "8" << endl;
	}
}

void Engine::checkPlayerHealth() {
	checkMutex.lock();
	this->players.shrink_to_fit();
	for(Player* p : this->players) {
		ClientHandler* ch = this->playerToClient[p];
		if(p->health <= 0) {
			ch->canSend = false;
			Room* prevRoom = p->currentRoom;
			this->roomHandler->start()->addPlayer(p);
			prevRoom->removePlayer(p);
			ch->canSend = true;
			ch->sendMessage(string("\nYou have died.\nIt is better to live for the emperor, than to die for yourself.\n"));
			ch->sendMessage(this->parser->printIntro());
			p->roomInfo(ch);
			p->health = 100;
		}
	}
	checkMutex.unlock();
}

void Engine::checkActorHealth() {
	checkMutex.lock();
	vector<Actor*> toDelete;
	for(int i = 0; i < this->roomHandler->npcMap.size(); ++i) {
		Actor* actor = this->roomHandler->npcMap[i];
		if(actor->health <= 0) {
			for(Player* p : actor->currentRoom->playersInRoom) {
				ClientHandler* ch = this->playerToClient[p];
				ch->sendMessage(string("\n" + actor->name + " has died.\n> "));
			}
			actor->die(this);
			delete actor;
			--i;
		}
	}
	this->roomHandler->npcMap.shrink_to_fit();
	checkMutex.unlock();
}

void Engine::addPlayer(ClientHandler* c, string name) {
	Player* p = new Player();
	p->name = name;
	p->currentRoom = this->roomHandler->start();
	this->roomHandler->start()->addPlayer(p);
	if(p->askedForName == false) {
		c->sendMessage(string("\nWhat is your name?\n> "));
		c->canSend = false;
	}
	this->clientToPlayer[c] = p;
	this->playerToClient[p] = c;

	this->players.push_back(p);
}

void Engine::parseInput(ClientHandler* ch, string str) {
	globalMutex.lock();
	Player* p = this->clientToPlayer[ch];
	parser->processCommand(p, ch, str);
	this->checkActorHealth();
	this->checkPlayerHealth();
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