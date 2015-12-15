#include "parser.hpp"

#include <string>

string Parser::getCommand() {
	return this->command[word::GO];
}

//TODO efter dusch: fixa parsern och loopen!