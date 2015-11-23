
#include "clientHandler.hpp"

using namespace std;


//Error handling
void client_error(const char *msg)
{
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
void ClientHandler::outProcess(int sock) {
	int n;
   	char buffer[256];
   	fd_set set;
    struct timeval timeout;

	while(1) 
	{

   		if(kill_everythread.load()) 
   		{
   			close(sock);
   			break;
   		}

   		std::cout << "Writing hello" << std::endl;
		n = write(sock,"Hello, I'm a server, and I am very much alive",45);

	   	if (n < 0) 
	   	{
	   		std::cout << "Error when Writing" << std::endl;
	   		close(sock);
	   		return;
	   	}

	   	usleep(4000000);
	}
}

/*
	Handles the input
*/
void ClientHandler::inProcess(int sock) {
	int n;
   	char buffer[256];
   	fd_set set;
    struct timeval timeout;

	while(1) {

   		if(kill_everythread.load()) {
   			close(sock);
   			break;
   		}

   		bzero(buffer,256); // empty buffer
		FD_ZERO(&set); /* clear the set */
		FD_SET(sock, &set); /* add our file descriptor to the set */

		timeout.tv_sec = 5; // set timer to 2 sec
		timeout.tv_usec = 0; // set return signal
   		
   		int ret = select(sock + 1, &set, NULL,
   		 NULL, &timeout);

   		if(ret != 0) {
   			n = read(sock,buffer,255);

		   	if (n < 0) {
		   		std::cout << "Error when reading socket" << std::endl;
		   		std::cout << "Closing the connection" << std::endl;
		   		kill_everythread = true;
		   		close(sock);
		   		return;
		   	}

		   	if(n == 0) {
		   		std::cout << "We got an empty package, something is wrong, abort" << std::endl; // test
		   		close(sock);
		   		return;
		   	}

		   	std::cout << "Client said:";
		   	std::cout << buffer << std::endl;
   		} 
   		else {
   			std::cout << "Client is idle" << std::endl;
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
	if(this->canBeEnded()) {
		kill_everythread = true;
		in_thr.wait();
		out_thr.get();
		close(socket.load()); // close socket
		return true;
	} else {
		return false;
	}
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
