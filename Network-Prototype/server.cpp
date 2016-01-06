#include "server.hpp"

void server_error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Server::client_listener() {
	int newsockfd;
	socklen_t clilen;
    struct sockaddr_in cli_addr;
	listen(sockfd,5);
    clilen = sizeof(cli_addr);
   	fd_set set;
    struct timeval timeout;
    timeout.tv_sec = 1; // Sert timeout to 1 sec
    timeout.tv_usec = 0; // set return signal to 0
    int rv;

    while(1) {
    	
    	if(kill_everythread.load()) { // return from function
        	break;
        }

    	FD_ZERO(&set); /* clear the set */
    	FD_SET(sockfd, &set); /* add our file descriptor to the set */

    	rv = select(sockfd + 1, &set, NULL, NULL, &timeout);
         
     	if(rv < 0) {
     		server_error("Error when selecting");
     	}
        else if(rv > 0) {
         	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
         	if (newsockfd < 0) 
             	server_error("ERROR on accept");
         	else {
         		ClientHandler* cl = new ClientHandler(engine);
         		(*cl).start(newsockfd, cli_addr);
         		std::cout << (*cl).getIP();
         		this->list_mutex.lock();
         		engine->addPlayer(cl);
         		//this->client_list.push_back(cl);
         		this->list_mutex.unlock();
         	}
        }
    }
}

Server::Server() : client_list() , kill_everythread(false){
	this->engine = new Engine();
}

Server::~Server() {
	delete this->engine;
}

bool Server::start(char* c) {
	std::cout << "Starting server" << std::endl;
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	this->portn = atoi(c);

	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(this->portn);
	int bind_return = ::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (bind_return < 0) {
    	server_error("ERROR on binding");
    } 
    //Start a thread which listens to the clients
	this->thread_starter = std::async(std::launch::async, &Server::client_listener, this);
}

/*
*
*
*/
bool Server::stop() {
	kill_everythread = true; // This will kill all the threads
	std::cout << "Waiting for thread starter" << std::endl;
	thread_starter.wait(); // Wait for the thread to finish
	std::cout << "Close socket" << std::endl;
	close(this->sockfd); // close socket
	//this->list_mutex.lock(); // lock the list
	std::cout << "locking list" << std::endl;
	engine->killConnections();
	engine->memHandle();
	/*for(ClientHandler* c: client_list) {
		std::cout << "Deletes clients" << std::endl;
		(*c).quitConnection(); // Kill all clients
		delete c; // delete list
	}
	*/
	//this->list_mutex.unlock(); // unlock the list
	return true; //TODO
	std::cout << "Server is killed" << std::endl;
}


atomic<bool> end_server;

void admin_input() {
	while(1) {
		std::string s;
		std::cin >> s;
		if(s == "end" || s == "End" || s == "exit" || s == "Exit") {
			end_server = true;
			std::cout << "Server is shutting down" << std::endl;
			break;
		}
	}
}


int main(int argc, char*argv[]) {
	try {
		if (argc < 2) {
	         fprintf(stderr,"ERROR, no port provided\n");
	         exit(1);
	    }

	    Server server;
	    server.start(argv[1]);
	    auto admin_thread = std::async(std::launch::async, admin_input);

	    while(1) {
	    	if(end_server.load()) {
	    		std::cout << "Kill the server" << std::endl;
	    		server.stop();
	    		return 0;
	    	}
	    	usleep(1000);
	    }
	}
	catch(std::exception const &exc)
    {
        std::cerr << "Exception caught " << exc.what() << "\n";
    }
}


