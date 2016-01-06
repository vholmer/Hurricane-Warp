#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <unordered_map>

#include "parser.hpp"
#include "player.hpp"
#include "../Network-Prototype/clientHandler.hpp"

struct Parser;
struct Player;
struct ClientHandler;

struct Engine {

	Parser* parser;
	unordered_map<Player*, ClientHandler*> playerToClient;
	unordered_map<ClientHandler*, Player*> clientToPlayer;
	RoomHandler* roomHandler;

	Engine();

	~Engine() {
		memHandle();
	}

	void memHandle();

	void killConnections();

	string printIntro();

	void tickActors();

	void addPlayer(ClientHandler* c);

	bool parseInput(ClientHandler* ch, string str);

	//void startGameLoop();

	void respawn();
};

#endif