files = main.cpp
files += engine.cpp
files += parser.cpp
files += player.cpp
files += item.cpp
files += roomhandler.cpp
files += room.cpp
files += actor.cpp
files += wizard.cpp
#files += troll.cpp troll.hpp
#files += villager.cpp villager.hpp

network = ../Network-Prototype/

files += $(network) server.cpp
files += $(network) clientHandler.cpp
files += $(network) network.cpp
files += $(network) socket.cpp

all:
	g++ -std=c++11 $(files) -lpthread

clean:
	rm -rf *.out.dSYM
	rm *.hpp.gch
	rm *.out
	rm *.hpp.*
