#include "parser.hpp"

Parser::Parser() {
	setUpCommands();
}

void Parser::setUpLambdas(Player* p) {
	this->funcMap[cmd::GO] = [this, p] (string secondWord = "") {
		if(secondWord == "") {
			cout << "Go where?" << endl;
			return false;
		}
		if(p->getExitMap().find(secondWord) != p->getExitMap().end()) {
			if(p->getRoomInDir(secondWord) != 0) {
				Room* nextRoom = p->getRoomInDir(secondWord);
				Room* prevRoom = p->currentRoom;
				nextRoom->addPlayer(p);
				prevRoom->removePlayer(p);
				p->roomInfo();
			}
		} else {
			cout << "You can't go there." << endl;
		}
		return false;
	};

	this->funcMap[cmd::LOOK] = [this, p] (string secondWord = "") {
		p->roomInfo();
		return false;
	};

	this->funcMap[cmd::HELP] = [this] (string secondWord = "") {
		cout << "God can't help you now!" << endl;
		return false;
	};

	this->funcMap[cmd::QUIT] = [this] (string secondWord = "") {
		return true;
	};

	this->funcMap[cmd::INVENTORY] = [this] (string secondWord = "") {
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

vector<string> Parser::getInput(string str) {
	std::stringstream s(str);

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

bool Parser::processCommand(Player* p, string str) {
	this->setUpLambdas(p);
	cout << "> ";
	vector<string> input = getInput(str);

	string firstWord = toLowerCase(input[0]);
	string secondWord;
	if(input.size() >= 2)
		secondWord = toLowerCase(input[1]);

	if(commands.find(firstWord) != commands.end()) {
		cmd token = commands[firstWord];
		return this->funcMap[token](secondWord);
	}
	cout << "What do you mean?" << endl;
	return false;
}