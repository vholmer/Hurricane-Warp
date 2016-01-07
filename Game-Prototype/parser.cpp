#include "parser.hpp"

Parser::Parser() {
	setUpCommands();
}

void Parser::setUpLambdas(Player* p, ClientHandler* ch) {
	this->funcMap[cmd::GO] = [this, p, ch] (string secondWord = "") {
		if(secondWord == "") {
			ch->sendMessage(string("Go where?\n"));;
			return;
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
			ch->sendMessage(string("You can't go there.\n> "));
		}
	};

	this->funcMap[cmd::LOOK] = [this, p, ch] (string secondWord = "") {
		p->roomInfo(ch);
	};

	this->funcMap[cmd::HELP] = [this, ch] (string secondWord = "") {
		ch->sendMessage(string("God can't help you now!\n> "));
	};

	this->funcMap[cmd::INVENTORY] = [this, p, ch] (string secondWord = "") {
		ch->sendMessage(p->printInventory());
	};

	this->funcMap[cmd::TAKE] = [this, p, ch] (string secondWord = "") {
		for(Item* inRoom : p->currentRoom->itemsInRoom) {
			if(toLowerCase(inRoom->name) == secondWord) {
				p->addItem(inRoom);
				ch->sendMessage(string("Added " + inRoom->name + " to inventory.\n> "));
				return;
			}
		}
		ch->sendMessage(string("That item is not here.\n> "));
	};
}

void Parser::setUpCommands() {
	this->commands["go"] = cmd::GO; 
	this->commands["look"] = cmd::LOOK;
	this->commands["help"] = cmd::HELP;
	this->commands["inventory"] = cmd::INVENTORY;
	this->commands["take"] = cmd::TAKE;
	this->commands["drop"] = cmd::DROP;
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

string Parser::printIntro() {
	string retString;
	retString += "You have crashed on a mysterious planet!\n";
	retString += "In the name of the Emperor, good luck.\n";
	retString += "What do you do?\n\n";
	return retString;
}

void Parser::processCommand(Player* p, ClientHandler* ch, string str) {
	this->setUpLambdas(p, ch);
	vector<string> input = getInput(str);

	if(p->askedForName == false) {
		if(input.size() > 2) {
			ch->sendMessage(string("Name too long!\n"));
		}
		p->name = str;
		p->askedForName = true;
		ch->sendMessage(this->printIntro());
		p->roomInfo(ch);
		return;
	}

	string firstWord = toLowerCase(input[0]);
	string secondWord;
	if(input.size() >= 2)
		secondWord = toLowerCase(input[1]);

	if(commands.find(firstWord) != commands.end()) {
		cmd token = commands[firstWord];
		this->funcMap[token](secondWord);
		return;
	}
	ch->sendMessage(string("What do you mean?\n> "));
}