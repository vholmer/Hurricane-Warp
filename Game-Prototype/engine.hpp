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
#include "../Network-Prototype/clientHandler.hpp"

struct Parser;
struct Player;
struct ClientHandler;
struct RoomHandler;

struct Engine {

	Parser* parser;
	unordered_map<Player*, ClientHandler*> playerToClient;
	unordered_map<ClientHandler*, Player*> clientToPlayer;
	RoomHandler* roomHandler;

	bool spin;

	future<void> managerThread;
	future<void> tickThread;

	Engine();

	~Engine() {
		memHandle();
	}

	void clientManager();

	void deleteClient(Player* p, ClientHandler* ch);

	void memHandle();

	void killConnections();

	void tickActors();

	void checkHealth(Player* p, ClientHandler* ch);

	void addPlayer(ClientHandler* c, string name = "");

	void parseInput(ClientHandler* ch, string str);

	//void startGameLoop();
};

#endif