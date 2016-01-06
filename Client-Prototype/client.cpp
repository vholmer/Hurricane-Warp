#include "client.hpp"

using namespace std;

using namespace Socket;

using namespace Network;

/*
	Thread which reads everything from the server
*/
void Client::read_process(int socket) {	
	int n;
   	char buffer[256];
   	fd_set set;
    struct timeval timeout;

	while(1) {

		//std::cout << "We are still in output" << std::endl;

		if(kill_everythread.load()) {
			//std::cout << "Breaking from output" << std::endl;
   			break;
   		}

		FD_ZERO(&set); /* clear the set */
		FD_SET(socket, &set); /* add our file descriptor to the set */
		timeout.tv_sec = 1; // set time out time  to 2 sec
		timeout.tv_usec = 0; // set return signal
   		
   		int ret = select(socket + 1, &set, NULL, NULL, &timeout);

   		if(ret != 0) {
		   	HandleInput(socket);
   		} 
   		
	}

}


void Client::HandleInput(int socket) {
	int n;
	int read;
	n = ReadInt(&read, socket);
	if(n < 0) return;
	MessageCode code = (MessageCode) read;
	MessageStruct* strc = NULL;

	switch (code) {
		case MessageCode::Default : {
			//std::cout << "Default" << std::endl;
			break;
			}
		case MessageCode::StillThere : {
			////std::cout << "Server asked if  I am still here" << std::endl;
			SendInt((int)MessageCode::StillHere, socket);
			break;
			}
		case MessageCode::MessageMessage :{
			////std::cout << "Message" << std::endl;
			MessageStruct* tmp = new MessageStruct();
			ReadMessageStruct(*tmp, socket);
			////std::cout << "Server said: " << std::endl;
			//std::cout << tmp->text << std::endl; 
			strc = tmp;
			break;
			}
		case MessageCode::ConnectionLost : {
			////std::cout << "Damn" << std::endl;
			////std::cout << "Server is down" << std::endl;
			n = SendInt((int)MessageCode::ConnectionLost, socket);
			
			if(n < 0) {
				///std::cout << "Something has gone completely wrong" << std::endl;
				return;
			}
			endConnection(socket);
			break;
			}
		default : {
			////std::cout << "Random input" << std::endl;
		}
	}
	if(strc != NULL)
		std::cout << strc->text << std::endl;
	delete strc;
}


void Client::endConnection(int socket) {
	this->kill_everythread = true;
	close(socket);
}

void Client::quitConnection(int socket) {
	this->kill_everythread = true;
	usleep(2000000);
	////std::cout << "Send quit request to server" << std::endl;
	int end = (int) MessageCode::ConnectionLost;
	SendInt(end, socket);

	////std::cout << "Waiting for response" << std::endl;
	int done = (int) MessageCode::ConnectionLost;
	int ret = 0;
	do {
		ReadInt(&ret, socket);
	} while(ret != done);
	SendInt(end, socket);
	////std::cout << "Kill the thread" << std::endl;

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
	MessageStruct strc;
	strc.textSize = s.size() + 1;
	//std::cout << "Gonna convert: " << s << std::endl;
	SetContentCharArray(s, strc.text, strc.textSize);
	//std::cout << "Sending: " << strc.text << std::endl;
	int n = SendMessageStruct(strc, socket);
}


/*
	The process that reads input from the client
*/
void Client::client_process(int socket) {
	while(1) {

		if(this->kill_everythread.load()) {
			//std::cout << "We are closing our connection" << std::endl;
			close(socket);
			break;
		}

		struct timeval tv;
	    fd_set fds;
	    tv.tv_sec = 3; // Set time out to 3 sec
	    tv.tv_usec = 0; // Set return code to 0
	    
	    FD_ZERO(&fds); // empty fds
	    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0

	    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv); //wait for std:cin input or timeout
	    int n = FD_ISSET(STDIN_FILENO, &fds);

	    if(n != 0) { // if no timeout
	    	string s;
	    	getline(cin, s);

	    	if(s == "Exit") {
	    		std::cout << "We are exiting" << std::endl;
	    		this->quitConnection(socket);
	    	}
	    	else {
	    		//std::cout << "Got a string" << std::endl;
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

	//std::cout << "starting client" << std::endl;
	if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    this->portno = atoi(argv[2]); // Connec
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    sock = sockfd;

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
    //std::cout << "We are logging out" << std::endl;
    return true;
}


bool Client::end() {
	return true; //TODO(Lukas)
}


int main(int argc, char* argv[]) {
	
	struct sigaction sigIntHandler;

   	sigIntHandler.sa_handler = OnExit;
   	sigemptyset(&sigIntHandler.sa_mask);
   	sigIntHandler.sa_flags = 0;

  	sigaction(SIGINT, &sigIntHandler, NULL);

	Client c;
	c.start(argc, argv); // Currently this is all that is neeeded
}

