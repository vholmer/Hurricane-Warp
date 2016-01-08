#include "engine.hpp"

using namespace std;

mutex globalMutex;
mutex checkMutex;
mutex disconMutex;

Engine::Engine() {
	this->parser = new Parser(this);
	this->roomHandler = new RoomHandler();
	this->spin = true;
	this->tickThread = async(std::launch::async, &Engine::tickActors, this);
	this->managerThread = async(std::launch::async, &Engine::clientManager, this);

}

void Engine::globalBroadcast(string message) {
	for(Player* p : this->players) {
		ClientHandler* ch = this->playerToClient[p];
		ch->sendMessage(string("\n" + message));
	}
}

void Engine::broadcast(Actor* fromActor, Room* room, bool leftRoom) {
	for(Player* p : room->getPlayersInRoom()) {
		ClientHandler* ch = this->playerToClient[p];
		if(leftRoom)
			ch->sendMessage(string("\n" + fromActor->getName()
				+ " has left the room.\n> "));
		else
			ch->sendMessage(string("\n" + fromActor->getName()
				+ " has entered the room.\n> "));
	}
}

void Engine::broadcastItem(Player* p, string itemName, bool pickedUp) {
	for(Player* otherInRoom : p->getRoom()->getPlayersInRoom()) {
		if(otherInRoom != p) {
			ClientHandler* ch = this->playerToClient[otherInRoom];
			if(pickedUp)
				ch->sendMessage(string("\n" + p->getName() + " took " + itemName + "\n> "));
			else
				ch->sendMessage(string("\n" + p->getName() + " dropped " + itemName + "\n> "));
		}
	}
}

void Engine::broadcastPlayerDamage(Actor* fromActor, Player* p, int dmg) {
	for(Player* other : fromActor->getRoom()->getPlayersInRoom()) {
		ClientHandler* ch = this->playerToClient[other];
		if(other != p)
			ch->sendMessage(string("\n" + p->getName()
				+ " was hit by " + fromActor->getName()
				+ " for " + to_string(dmg) + " damage.\n> "));
		else
			ch->sendMessage(string("\nYou were hit by "
				+ fromActor->getName() + " for "
				+ to_string(dmg) + " damage."
				+ " (" + to_string(p->getHealth())
				+ "/" + to_string(p->getMaxHealth())
				+ ")HP"
				+ "\n> "));
	}
}

void Engine::clientManager() {
	while(this->spin) {
		disconMutex.lock();
		checkMutex.lock();
		usleep(100000);
		for(ClientHandler* ch : this->disconList) {
			globalMutex.lock();
			Player* p = this->clientToPlayer[ch];
			p->dropAllItems(this);
			for(Item* item : p->getInventory()) {
				delete item;
			}
			p->getRoom()->removePlayer(p);
			auto begiP = this->players.begin();
			auto endP  = this->players.end();
			for(auto i = begiP; i != endP; ++i) {
				if(*i == p) {
					this->players.erase(i);
					this->players.shrink_to_fit();
					break;
				}
			}
			auto begin = this->disconList.begin();
			auto end = this->disconList.end();
			for(auto i = begin; i != end; ++i) {
				if(*i == ch) {
					this->disconList.erase(i);
					break;
				}
			}
			this->playerToClient.erase(p);
			this->clientToPlayer.erase(ch);
			delete ch;
			delete p;
			globalMutex.unlock();
			break;
		}
		checkMutex.unlock();
		disconMutex.unlock();
	}
}

void Engine::setDisconnected(ClientHandler* ch) {
	disconMutex.lock();
	this->disconList.push_back(ch);
	disconMutex.unlock();
}

void Engine::memHandle() {
	this->spin = false;
	this->tickThread.wait();
	this->managerThread.wait();

	delete this->parser;

	for(pair<Player*, ClientHandler*> p : this->playerToClient) {
		for(Item* item : p.first->getInventory()) {
			delete item;
		}
		delete p.first;
		delete p.second;

	}
	for(Room* room : this->roomHandler->gameMap) {

		for(Item* item : room->getItemsInRoom()) {
			delete item;
		}

		for(Actor* actor : room->getCharsInRoom()) {
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
		string daemon = "Daemon";
		bool daemonAlive= false;
		for(Actor* actor : this->roomHandler->npcMap) {
			if(actor->getName() == daemon)
				daemonAlive = true;
		}
		if(!daemonAlive) {
			this->roomHandler->spawnDaemon(this);
		}
		cout << "6" << endl;
		checkMutex.unlock();
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
		if(p->getHealth() <= 0) {
			Room* prevRoom = p->getRoom();
			p->dropAllItems(this);
			p->broadcastDeath(this);
			this->roomHandler->start()->addPlayer(p);
			prevRoom->removePlayer(p);
			ch->sendMessage(string("\nYou have died.\nIt is better to die for the emperor, than to live for yourself.\n"));
			ch->sendMessage(this->parser->getIntro());
			p->roomInfo(ch);
			p->setHealth(p->getMaxHealth());
		}
	}
	checkMutex.unlock();
}

void Engine::checkActorHealth() {
	checkMutex.lock();
	vector<Actor*> toDelete;
	for(int i = 0; i < this->roomHandler->npcMap.size(); ++i) {
		Actor* actor = this->roomHandler->npcMap[i];
		if(actor->getHealth() <= 0) {
			for(Player* p : actor->getRoom()->getPlayersInRoom()) {
				ClientHandler* ch = this->playerToClient[p];
				ch->sendMessage(string("\n" + actor->getName() + " has died.\n> "));
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
	p->setName(name);
	p->setRoom(this->roomHandler->start());
	this->roomHandler->start()->addPlayer(p);
	if(p->askedName() == false) {
		c->sendMessage(string("\n")
			+ string("Welcome to Hurricane Warp. Type help if you get stuck!\n")
			+ string("What is your name?\n> "));
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