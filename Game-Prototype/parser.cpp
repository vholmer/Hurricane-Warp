#include "parser.hpp"

Parser::Parser(Engine* engine) {
	setUpCommands();
	this->engine = engine;
}

void Parser::setUpLambdas(Player* p, ClientHandler* ch) {
	this->funcMap[cmd::GO] = [this, p, ch] (string secondWord = "") {
		if(secondWord == "") {
			ch->sendMessage(string("Go where?\n> "));;
			return;
		}
		if(p->getExitMap().find(secondWord) != p->getExitMap().end()) {
			if(p->getRoomInDir(secondWord) != 0) {
				Room* nextRoom = p->getRoomInDir(secondWord);
				Room* prevRoom = p->getRoom();
				nextRoom->addPlayer(p);
				prevRoom->removePlayer(p);
				p->roomInfo(ch);
				this->broadcastMovement(p, prevRoom);
			}
		} else {
			ch->sendMessage(string("You can't go there.\n> "));
		}
	};

	this->funcMap[cmd::LOOK] = [this, p, ch] (string secondWord = "") {
		p->roomInfo(ch);
	};

	this->funcMap[cmd::HELP] = [this, ch] (string secondWord = "") {
		string toSend = "The Emperor protects, these are your commands:\n";
		for(pair<string, cmd> p : this->commands) {
			toSend += p.first + " ";
		}
		toSend += "\n> ";
		ch->sendMessage(string(toSend));
	};

	this->funcMap[cmd::INVENTORY] = [this, p, ch] (string secondWord = "") {
		ch->sendMessage(p->getInventoryString());
	};

	this->funcMap[cmd::TAKE] = [this, p, ch] (string secondWord = "") {
		for(Item* inRoom : p->getRoom()->getItemsInRoom()) {
			if(toLowerCase(inRoom->getName()) == secondWord) {
				p->addItem(inRoom, engine);
				return;
			}
		}
		ch->sendMessage(string("That item is not here.\n> "));
	};

	this->funcMap[cmd::DROP] = [this, p, ch] (string secondWord = "") {
		for(Item* item : p->getInventory()) {
			if(secondWord == toLowerCase(item->getName())) {
				p->dropItem(item, engine);
				ch->sendMessage(string("> "));
				return;
			}
		}
		ch->sendMessage(string("You don't have that item.\n> "));
	};

	this->funcMap[cmd::FIGHT] = [this, p, ch] (string secondWord = "") {
		if(secondWord == "") {
			ch->sendMessage(string("Fight who?\n> "));
			return;
		}
		if(secondWord == toLowerCase(p->getName())) {
			ch->sendMessage(string("You cannot fight yourself!\n> "));
			return;
		}
		for(Player* otherPlayer : p->getRoom()->getPlayersInRoom()) {
			if(toLowerCase(otherPlayer->getName()) == secondWord) {
				int damageDone = p->fightPlayer(otherPlayer);

				ch->sendMessage(string("You hit "
					+ otherPlayer->getName()
					+ " for "
					+ to_string(damageDone)
					+ " damage.\n> "));

				ClientHandler* otherCh = this->engine->playerToClient[otherPlayer];
				otherCh->sendMessage(string("\n"
					+ p->getName() + "hit you for "
					+ to_string(damageDone) + " damage."
					+ " (" + to_string(otherPlayer->getHealth())
					+ "/" + to_string(otherPlayer->getMaxHealth())
					+ ")HP"
					+ "\n> "));

				return;
			}
		}
		for(Actor* actor : p->getRoom()->getCharsInRoom()) {
			if(toLowerCase(actor->getName()) == secondWord) {
				int damageDone = p->fightActor(actor);

				ch->sendMessage(string("You hit "
					+ actor->getName()
					+ " for "
					+ to_string(damageDone)
					+ " damage.\n> "));

				return;
			}
		}
		ch->sendMessage(string("That person is not here.\n> "));
	};

	this->funcMap[cmd::EXAMINE] = [this, p, ch] (string secondWord = "") {
		bool foundItem = false;
		if(!foundItem) {
			for(Item* inRoom : p->getRoom()->getItemsInRoom()) {
				if(toLowerCase(inRoom->getName()) == secondWord) {
					ch->sendMessage(string(inRoom->getDescription()));
					foundItem = true;
					break;
				}
			}
		}
		if(!foundItem) {
			for(Item* inInv : p->getInventory()) {
				if(toLowerCase(inInv->getName()) == secondWord) {
					ch->sendMessage(string(inInv->getDescription()));
					foundItem = true;
					break;
				}
			}
		}
		if(foundItem)
			ch->sendMessage(string("\n> "));
		else
			ch->sendMessage(string("That item does not exist.\n> "));
	};
}

void Parser::setUpCommands() {
	this->commands["go"] = cmd::GO; 
	this->commands["look"] = cmd::LOOK;
	this->commands["help"] = cmd::HELP;
	this->commands["inventory"] = cmd::INVENTORY;
	this->commands["take"] = cmd::TAKE;
	this->commands["drop"] = cmd::DROP;
	this->commands["fight"] = cmd::FIGHT;
	this->commands["examine"] = cmd::EXAMINE;
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

string Parser::getIntro() const {
	string retString;
	retString += "You have crashed on a mysterious planet!\n";
	retString += "In the name of the Emperor, good luck.\n";
	retString += "What do you do?\n\n";
	return retString;
}

void Parser::broadcastMovement(Player* p, Room* prevRoom) {
	for(Player* otherInRoom : p->getRoom()->getPlayersInRoom()) {
		if(otherInRoom != p) {
			ClientHandler* ch = this->engine->playerToClient[otherInRoom];
			ch->sendMessage(string("\n" + p->getName() + " has entered the room.\n> "));
		}
	}
	for(Player* otherInRoom : prevRoom->getPlayersInRoom()) {
		ClientHandler* ch = this->engine->playerToClient[otherInRoom];
		ch->sendMessage(string("\n" + p->getName() + " has left the room.\n> "));
	}
}

void Parser::processCommand(Player* p, ClientHandler* ch, string str) {
	this->setUpLambdas(p, ch);
	vector<string> input = getInput(str);

	if(p->askedName() == false) {
		if(input.size() > 2) {
			ch->canSend = true;
			ch->sendMessage(string("Name too long!\n"));
			ch->canSend = false;
		}
		p->setName(input[0]);
		p->setAskedName(true);
		ch->canSend = true;
		ch->sendMessage(this->getIntro());
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