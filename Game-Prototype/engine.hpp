#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "parser.hpp"
#include "player.hpp"

struct Parser;
struct Player;

struct Engine {
	Parser* parser;
	Player* player;
	RoomHandler* roomHandler;

	Engine();

	~Engine() {
		memHandle();
	}

	void memHandle();

	void printIntro();

	void tickActors();

	void startGameLoop();

	void respawn();
};

#endif