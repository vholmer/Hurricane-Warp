#include "parser.hpp"

Parser::Parser(Player* player) {
	this->player = player;
	setUpCommands();
}

void Parser::setUpCommands() {
	this->commands["go"] = cmd::GO; 
	this->commands["look"] = cmd::LOOK;
	this->commands["help"] = cmd::HELP;
	this->commands["quit"] = cmd::QUIT;
}

vector<string> Parser::getInput() {
	string input;
	getline(cin, input);
	std::stringstream s(input);

	vector<string> inpVec;

	while(!s.eof()) {
		string tmp;
		s >> tmp;
		inpVec.push_back(tmp);
	}

	return inpVec;
}

string Parser::toLowerCase(string str) {
	locale loc;
	string result;
	for(int i = 0; i < str.size(); ++i) {
		result += tolower(str[i], loc);
	}
	return result;
}

bool Parser::processCommand() {
	cout << "> ";
	vector<string> input = getInput();

	string firstWord = toLowerCase(input[0]);
	string secondWord;
	if(input.size() >= 2)
		secondWord = toLowerCase(input[1]);

	switch(commands[firstWord]) {
		case cmd::GO:
			if(input.size() != 2) {
				cout << "Go where?" << endl;
				break;
			}
			if(player->currentRoom->exits[secondWord] != 0) {
				Room* nextRoom = player->getExits(secondWord);
				player->currentRoom = nextRoom;
				player->roomInfo();
			} else {
				cout << "You can't go there." << endl;
			}
			break;
		case cmd::LOOK:
			player->roomInfo();
			break;
		case cmd::HELP:
			cout << "God can't help you now!" << endl;
			break;
		case cmd::QUIT:
			return true;
		default:
			cout << "What do you mean?" << endl;
			break;
	}
	return false;
}