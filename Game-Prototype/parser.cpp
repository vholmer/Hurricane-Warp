#include "parser.hpp"

Parser::Parser() {
	setUpCommands();
}

void Parser::setUpLambdas(Player* p, ClientHandler* ch) {
	this->funcMap[cmd::GO] = [this, p, ch] (string secondWord = "") {
		if(secondWord == "") {
			ch->sendMessage(string("Go where?\n"));;
			return false;
		}
		if(p->getExitMap().find(secondWord) != p->getExitMap().end()) {
			if(p->getRoomInDir(secondWord) != 0) {
				Room* nextRoom = p->getRoomInDir(secondWord);
				Room* prevRoom = p->currentRoom;
				nextRoom->addPlayer(p);
				prevRoom->removePlayer(p);
				p->roomInfo(ch);
			}
		} else {
			ch->sendMessage(string("You can't go there.\n"));
		}
		return false;
	};

	this->funcMap[cmd::LOOK] = [this, p, ch] (string secondWord = "") {
		p->roomInfo(ch);
		return false;
	};

	this->funcMap[cmd::HELP] = [this, ch] (string secondWord = "") {
		ch->sendMessage(string("God can't help you now!\n"));
		return false;
	};

	this->funcMap[cmd::QUIT] = [this] (string secondWord = "") {
		return true;
	};

	this->funcMap[cmd::INVENTORY] = [this, ch] (string secondWord = "") {
		ch->sendMessage(string("You have nothing!\n"));
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

bool Parser::processCommand(Player* p, ClientHandler* ch, string str) {
	this->setUpLambdas(p, ch);
	vector<string> input = getInput(str);

	string firstWord = toLowerCase(input[0]);
	string secondWord;
	if(input.size() >= 2)
		secondWord = toLowerCase(input[1]);

	if(commands.find(firstWord) != commands.end()) {
		cmd token = commands[firstWord];
		return this->funcMap[token](secondWord);
	}
	ch->sendMessage(string("What do you mean?\n"));
	return false;
}