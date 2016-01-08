#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <unordered_map>
#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <unistd.h>

#include "parser.hpp"
#include "player.hpp"
#include "actor.hpp"
#include "../Network-Prototype/clientHandler.hpp"

struct Parser;
struct Player;
struct ClientHandler;
struct RoomHandler;
struct Actor;

struct Engine {

private:
	future<void> managerThread;
	future<void> tickThread;

	Parser* parser;
	unordered_map<ClientHandler*, Player*> clientToPlayer;

	bool spin;

	vector<Player*> players;
	vector<ClientHandler*> disconList;

public:
	RoomHandler* roomHandler;

	unordered_map<Player*, ClientHandler*> playerToClient;
	
	Engine();

	~Engine() {
		std::cout << "Memhandlar" << std::endl;
		memHandle();
		std::cout << "Finnishing MemHandler" << std::endl;
	}

	void globalBroadcast(string message);

	void broadcast(Actor* fromActor, Room* prevRoom, bool leftRoom);

	void broadcastItem(Player* p, string itemName, bool pickedUp);

	void broadcastPlayerDamage(Actor* fromActor, Player* p, int dmg);

	void clientManager();

	void setDisconnected(ClientHandler* ch);

	void deleteClient(Player* p, ClientHandler* ch);

	void memHandle();

	void killConnections();

	void tickActors();

	void checkPlayerHealth();

	void checkActorHealth();

	void addPlayer(ClientHandler* c, string name = "");

	void parseInput(ClientHandler* ch, string str);

	//void startGameLoop();
};

#endif