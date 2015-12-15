#include "parser.hpp"

Parser::Parser(Player* player) {
	this->player = player;
	setUpCommands();
}

void Parser::setUpCommands() {
	this->commands["go"] = GO; 
	this->commands["look"] = LOOK;
	this->commands["help"] = HELP;
	this->commands["quit"] = QUIT;
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
	cout << "firstWord: " << firstWord << endl;

	switch(commands[firstWord]) {
		case GO:
			cout << "Command go!" << endl;
			break;
		case LOOK:
			cout << "Command look!" << endl;
			break;
		case HELP:
			cout << "God can't help you now!" << endl;
			break;
		case QUIT:
			return true;
		default:
			cout << "What do you mean?" << endl;
			break;
	}
	return false;
}