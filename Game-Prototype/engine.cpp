#include <iostream>

#include "engine.hpp"

using namespace std;

Engine::Engine() {
	quitBoolean = false;
	parser = new Parser();
	player = new Player();
}

void Engine::memHandle() {
	delete parser;
	delete player;
}

void Engine::printIntro() {
	cout << "You have crashed!" << endl;
	cout << "In the name of the Emperor, good luck." << endl << endl;
}

void Engine::startGameLoop() {
	printIntro();
}

void Engine::quitGame() {
	quitBoolean = true;
}

void Engine::respawn() {
	cout << "No respawns lol" << endl;
}