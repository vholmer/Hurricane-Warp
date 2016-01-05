#include "parser.hpp"

Parser::Parser(Player* player) {
	this->player = player;
	setUpCommands();
	setUpLambdas();
}

void Parser::setUpLambdas() {
	funcMap[cmd::GO] = [this] (string secondWord = "") {
		if(secondWord == "") {
			cout << "Go where?" << endl;
			return false;
		}
		if(this->player->getExitMap().find(secondWord) != this->player->getExitMap().end()) {
			if(this->player->getExits(secondWord) != 0) {
				Room* nextRoom = this->player->getExits(secondWord);
				this->player->currentRoom = nextRoom;
				this->player->roomInfo();
			}
		} else {
			cout << "You can't go there." << endl;
		}
		return false;
	};

	funcMap[cmd::LOOK] = [this] (string secondWord = "") {
		this->player->roomInfo();
		return false;
	};

	funcMap[cmd::HELP] = [this] (string secondWord = "") {
		cout << "God can't help you now!" << endl;
		return false;
	};

	funcMap[cmd::QUIT] = [this] (string secondWord = "") {
		return true;
	};

	funcMap[cmd::INVENTORY] = [this] (string secondWord = "") {
		cout << "You have nothing!" << endl;
		return false;
	};
}

void Parser::setUpCommands() {
	this->commands["go"] = cmd::GO; 
	this->commands["look"] = cmd::LOOK;
	this->commands["help"] = cmd::HELP;
	this->commands["quit"] = cmd::QUIT;
	this->commands["inventory"] = cmd::INVENTORY;
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

	if(commands.find(firstWord) != commands.end()) {
		return funcMap[commands[firstWord]](secondWord);
	}
	cout << "What do you mean?" << endl;
	return false;
}