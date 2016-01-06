#include "clientHandler.hpp"


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
	int count = 0;
	while(1) {
		int n = 0;
		if(kill_everythread.load()) {
			close(socket);
			return;
		} else {
			if(count % 2 == 0) 	 {		
				std::string s = "FUCK";
				MessageStruct strc;
				strc.textSize = s.size() + 1;
				std::cout << "Gonna convert: " << s << std::endl;
				SetContentCharArray(s, strc.text, strc.textSize);
				std::cout << "Sending: " << strc.text << std::endl;
				int n = SendMessageStruct(strc, socket);
			} 
			else {
				std::string s = "Damn";
				MessageStruct strc;
				strc.textSize = s.size() + 1;
				std::cout << "Gonna convert: " << s << std::endl;
				SetContentCharArray(s, strc.text, strc.textSize);
				std::cout << "Sending: " << strc.text << std::endl;
				int n = SendMessageStruct(strc, socket);
			}
		}

		if (n < 0) {
			std::cout << "Error when Writing" << std::endl;
			close(socket);
			return;
		}
		++count;
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
	NetworkStruct* strc = NULL;
	switch (code) {
		case MessageCode::MessageMessage : {
			std::cout << "Message" << std::endl;
			MessageStruct* tmp = new MessageStruct();
			ReadMessageStruct(*tmp, socket);
			std::cout << "Server said: " << std::endl;
			std::cout << tmp->textSize << std::endl;
			std::cout << tmp->text << std::endl; 
			strc = tmp; 
			break;
			}
		default : {
			std::cout << "Protocol error" << std::endl;
		}
	}
	engine->parseInput(this, std::string(strc.text, strc.textSize));
	delete strc;
}


/*
 
*/
ClientHandler::ClientHandler(Engine* engine) {
	this->engine = engine;
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
	//out_thr = std::async(std::launch::async, &ClientHandler::outProcess, this, this->socket.load());
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
			//out_thr.wait();
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
	//auto status1 = out_thr.wait_for(std::chrono::milliseconds(0));
	auto status2 = in_thr.wait_for(std::chrono::milliseconds(0));
	//return //status1 == future_status::ready &&
	return status2 == future_status::ready;

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

/*
void ClientHandler::sendSpawn() {


} */

void ClientHandler::sendMessage(std::string s) {
	send_mutex.lock();
	MessageStruct strc;
	strc.textSize = s.size() + 1;
	std::cout << "Gonna convert: " << s << std::endl;
	SetContentCharArray(s, strc.text, strc.textSize);
	std::cout << "Sending: " << strc.text << std::endl;
	int n = SendMessageStruct(strc, socket.load());
	send_mutex.unlock();
}

/*
void ClientHandler::sendRoomInfo(Room* room) {

}
*/
