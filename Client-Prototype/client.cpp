#include "client.hpp"

using namespace std;

using namespace Socket;

/*
	Thread which reads everything from the server
*/
void Client::read_process(int socket) {	
	int n;
   	char buffer[256];
   	fd_set set;
    struct timeval timeout;

	while(1) {

		if(kill_everythread.load()) {
   			break;
   		}
   		//bzero(buffer,256); // empty buffer
		FD_ZERO(&set); /* clear the set */
		FD_SET(socket, &set); /* add our file descriptor to the set */

		timeout.tv_sec = 2; // set timer to 2 sec
		timeout.tv_usec = 0; // set return signal
   		
   		int ret = select(socket + 1, &set, NULL, NULL, &timeout);

   		if(ret != 0) {

		   	HandleInput(socket);
		   	if (n < 0) {
		   		std::cout << "Error when reading socket" << std::endl;
		   		close(socket);
		   		return;
		   	}

   		} 
   		
	}

}


void Client::HandleInput(int socket) {
	int n;
	int read;
	n = ReadInt(&read, socket);
	if(n < 0) return;
	MessageCode code = (MessageCode) read;

	switch (code) {
		case MessageCode::Default :
			std::cout << "Default" << std::endl;
			break;
		case MessageCode::RoomMessage :
			std::cout << "Room" << std::endl;
			break;
		case MessageCode::AttackMessage :
			std::cout << "Attack" << std::endl;
			break;
		case MessageCode::EnemyMessage :
			std::cout << "Enemy" << std::endl;
			break;
		case MessageCode::PlayerMessage :
			std::cout << "Player" << std::endl;
			break;
		case MessageCode::MessageMessage :
			std::cout << "MessageMessage" << std::endl;
			EndConnection(socket);
			break;
	}
}

void Client::EndConnection(int socket) {
	int end = (int) MessageCode::ConnectionLost;
	SendInt(end, socket);
	this->kill_everythread = true;
}


/*
void Client::outputAdded(NetworkStruct str) {
		this->output_mutex.lock();
		outgoing.push_back(str);
		this->output_mutex.unlock();
}

*/
/*
Room Client::requestRoom(int roomID) {
		RoomInfo str;
		srt.roomID = roomID;
		str.requestID = this->getNextRequestID();

		requestList.add(str.requestID);
		SendRoomRequest(str);
}
*/

unsigned int Client::getNextRequestID() {
	if(this->requestNumber == 0) {
		++(this->requestNumber);
	}
	return (this->requestNumber)++;
}



/*
	Send a string on a socket
*/
void Client::send(int socket, string s) {
	std::copy(s.begin(), s.end(), buffer);
	buffer[s.size()]=0;
	std::cout << buffer << std::endl;
	int message = (int) MessageCode::EnemyMessage;
	SendInt(message, socket);
}


/*
	The process that reads input from the client
*/
void Client::client_process(int socket) {
	while(1) {

		if(this->kill_everythread.load()) {
			std::cout << "We are closing our connection" << std::endl;
			close(socket);
			break;
		}

		struct timeval tv;
	    fd_set fds;
	    tv.tv_sec = 5;
	    tv.tv_usec = 0;
	    
	    FD_ZERO(&fds);
	    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0

	    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	    int n = FD_ISSET(STDIN_FILENO, &fds);

	    if(n != 0) {
	    	string s;
	    	cin >> s;

	    	if(s == "Exit") {
	    		std::cout << "We are exiting" << std::endl;
	    		this->kill_everythread = true;
	    		close(socket);
	    		break;
	    	}
	    	else {
	    		std::cout << "Got a string" << std::endl;
	    		send(socket, s);
	    	}
	    }

	}
}

/*
	Initiate the client
*/
Client::Client() : requestList(), incoming(), outgoing() {
	this->requestNumber = 1;
	this->kill_everythread = false;
}

/*
	Start connection with the server
*/
bool Client::start(int argc, char* argv[]) {

	std::cout << "starting client" << std::endl;
	if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    this->portno = atoi(argv[2]); // Connec
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (this->sockfd < 0) 
        error("ERROR opening socket");

    this->server = gethostbyname(argv[1]); // Get a host by IP adress
    
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // set everything to zero

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
     server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    auto test = async(std::launch::async, &Client::client_process, this, this->sockfd);
    auto test2 = async(std::launch::async, &Client::read_process, this, this->sockfd);
    test.wait();
    test2.wait();
    std::cout << "We are logging out" << std::endl;
    return true;
}


bool Client::end() {
	return true; //TODO
}





int main(int argc, char* argv[]) {
	Client c;
	c.start(argc, argv); // Currently this is all that is neeeded
}

