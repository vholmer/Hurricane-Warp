#include "clientHandler.hpp"

using namespace Socket;

using namespace Network;

//Error handling
void client_error(const char *msg)
{
	std::cout << "We got an error on our ass" << std::endl;
    perror(msg);
    exit(1);
}

/*
	
*/
string ClientHandler::calculateIP(struct sockaddr_in &cli_addr) const {
	return inet_ntoa(cli_addr.sin_addr);
}

/*
	The process that handles all output from the clienthandler
*/
void ClientHandler::outProcess(int socket) {
	while(1) {
		int n = 0;
		if(kill_everythread.load()) {
			close(socket);
			return;
		} else {
			char buffer [1024];
			std::string s = "日本国（にっぽんこく、にほんこく）、または日本（にっぽん、にほん）は、東アジアに位置する日本列島（北海道・本州・四国・九州の主要四島およびそれに付随する島々）及び、南西諸島・小笠原諸島などの諸島嶼から成る島国である[1]。日本語が事実上の公用語として使用されている。首都は事実上東京都とされている。";
			PlayerStruct strc;
			SetContentCharArray(s, strc.name, strc.namesize);
			strc.id = 1337;
			strc.namesize = s.size() + 1;
			int n = SendPlayerStruct(strc, socket);
		}

		if (n < 0) {
			std::cout << "Error when Writing" << std::endl;
			close(socket);
			return;
		}

		usleep(500000);
	}
}
/*
	Handles the input
*/
void ClientHandler::inProcess(int socket) {
   	fd_set set;
    struct timeval timeout;

    this->clientDead = false;
	while(1) {

   		if(kill_everythread.load()) {
   			close(socket);
   			break;
   		}

		FD_ZERO(&set); /* clear the set */
		FD_SET(socket, &set); /* add our file descriptor to the set */
		timeout.tv_sec = 5; // set timer to 5 sec
		timeout.tv_usec = 0; // set return signal
   		
   		int ret = select(socket + 1, &set, NULL,
   		 NULL, &timeout);

   		if(ret != 0) {
   			clientDead = false;
   			std::cout << "Gonna read" << std::endl;
   			std::cout << "Fuck" << std::endl;
   			HandleInput(socket);
   			std::cout << "Done reading" << std::endl;
   		} 
   		else {
   			std::cout << "Client is idle" << std::endl;
   			if(clientDead) {
   				endConnection();
   			} else {
   				SendInt((int) MessageCode::StillThere, socket);
   				clientDead = true;
   			}
   		}
	}
}

void ClientHandler::HandleInput(int socket) {
	std::cout << "In handle input" << std::endl;
	int n;
	int read;
	std::cout << "In more handle input" << std::endl;
	n = ReadInt(&read, socket);
	std::cout << "Trying to read" << std::endl;
	if(n < 0) return;
	MessageCode code = (MessageCode) read;

	std::cout << "We got: " << read << std::endl;

	switch (code) {
		case MessageCode::Default : {
			std::cout << "Default" << std::endl;
			break;
			}
		case MessageCode::RoomMessage : {
			std::cout << "Room" << std::endl;
			RoomStruct strc;
			ReadRoomStruct(strc, socket);
			std::cout << "id:" << strc.id << std::endl;
			break;
			}	
		case MessageCode::AttackMessage : {
			std::cout << "Attack" << std::endl;
			AttackStruct strc;
			ReadAttackStruct(strc, socket);
			std::cout << "attacker:" << strc.attackerID << std::endl;
			std::cout << "target:" << strc.targetID << std::endl;
			std::cout << "damage:" << strc.damage << std::endl;
			break;
			}
		case MessageCode::EnemyMessage : {
			std::cout << "Enemy" << std::endl;
			break;
			}
		case MessageCode::PlayerMessage : {
			std::cout << "Player" << std::endl;
			PlayerStruct strc;
			ReadPlayerStruct(strc, socket);
			std::cout << "id:" << strc.id << std::endl;
			std::cout << "name size:" << strc.namesize << std::endl;
			std::cout << "name:" << strc.name << std::endl;		
			break;
			}
		case MessageCode::MessageMessage : {
			std::cout << "Message" << std::endl;
			MessageStruct strc;
			ReadMessageStruct(strc, socket);
			std::cout << "Server said: " << std::endl;
			std::cout << strc.textSize << std::endl;
			std::cout << strc.text << std::endl;  
			break;
			}
		case MessageCode::StillHere : {
			this->clientDead = false;
			break;
			}
		case MessageCode::ConnectionLost : {
			std::cout << "End connection" << std::endl;
			std::cout << "We are done here" << std::endl;
			int i = (int) MessageCode::ConnectionLost;
			SendInt(i, socket);
			this->quitConnection();
			break;
			}
		default : {
			std::cout << "Random input" << std::endl;
		}
	}
}


/*
 
*/
ClientHandler::ClientHandler() {
	//maybe this should do something
}

/*

*/
bool ClientHandler::isStarted() const{
	return this->started;
}

/*
	Start up a connection
*/
bool ClientHandler::start(int sock, struct sockaddr_in &cli_addr) {
	kill_everythread = false;
	this->socket = sock;
	this->id = std::to_string(sock);
	this->ip_adress = calculateIP(cli_addr);
	in_thr = std::async(std::launch::async, &ClientHandler::inProcess, this, this->socket.load());
	out_thr = std::async(std::launch::async, &ClientHandler::outProcess, this, this->socket.load());
}

/*
	End the connection
*/
bool ClientHandler::endConnection() {
		kill_everythread = true;
		close(this->socket.load()); // close socket
		std::cout << "Tråden är färdig" << std::endl;
		return true;
}

bool ClientHandler::quitConnection() {
		std::cout << "End connection" << std::endl;
		if(kill_everythread.load()) {
			out_thr.wait();
			in_thr.wait();
			return true;
		}
		int end = (int) MessageCode::ConnectionLost;
		SendInt(end, this->socket.load());

		int done = (int) MessageCode::ConnectionLost;
		int ret = 0;
		do {
			ReadInt(&ret, this->socket);
		} while(ret != done);

		return this->endConnection();
}

/*
	Returns true if the connection can be ended without errors
*/
bool ClientHandler::canBeEnded() const {
	auto status1 = out_thr.wait_for(std::chrono::milliseconds(0));
	auto status2 = in_thr.wait_for(std::chrono::milliseconds(0));
	return status1 == future_status::ready &&
	status2 == future_status::ready;

}

/*
	Returns the ip of the client
*/
string ClientHandler::getIP() const {
	return this->ip_adress;
}

/*
	Get the id of the client
*/
string ClientHandler::getID() const {
	return this->id;
}
