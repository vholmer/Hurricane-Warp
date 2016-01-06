#include <time.h>

#include "engine.hpp"

int main(void) {
	srand(time(NULL));
	Engine game;
	game.addPlayer();
	game.startGameLoop();
	return 0;
}