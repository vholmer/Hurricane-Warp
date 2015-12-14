#include "parser.hpp"

struct Engine {
	bool quitBoolean;
	Parser* parser;
	Player* player;

	Engine();

	~Engine() {
		memHandle();
	}

	void memHandle();

	void printIntro();

	void startGameLoop();

	void quitGame();

	void respawn();
};