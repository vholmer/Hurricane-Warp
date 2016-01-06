#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

#include "parser.hpp"
#include "player.hpp"

struct Parser;
struct Player;

struct Engine {
	Parser* parser;
	vector<Player*> players;
	RoomHandler* roomHandler;

	Engine();

	~Engine() {
		memHandle();
	}

	void memHandle();

	void printIntro();

	void tickActors();

	void addPlayer();

	void startGameLoop();

	void respawn();
};

#endif