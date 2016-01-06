#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <map>

#include "parser.hpp"
#include "player.hpp"
#include "../Network-Prototype/clientHandler.hpp"

struct Parser;
struct Player;

struct Engine {

	Parser* parser;
	map<Player*, ClientHandler*> playerToClient;
	map<ClientHandler*, Player*> clientToPlayer;
	RoomHandler* roomHandler;

	Engine();

	~Engine() {
		memHandle();
	}

	void memHandle();

	void killConnections();

	void printIntro();

	void tickActors();

	void addPlayer(ClientHandler* ch);

	bool parseInput(ClientHandler* ch, string str);

	void startGameLoop();

	void respawn();
};

#endif