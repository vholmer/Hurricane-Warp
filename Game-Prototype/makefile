files = main.cpp
files += engine.cpp engine.hpp
files += parser.cpp parser.hpp
files += player.cpp player.hpp
files += item.cpp item.hpp
files += roomhandler.cpp roomhandler.hpp
files += room.cpp room.hpp
files += actor.cpp actor.hpp
files += wizard.cpp wizard.hpp
#files += troll.cpp troll.hpp
#files += villager.cpp villager.hpp

all:
	g++ -std=c++11 $(files)

clean:
	rm -rf *.out.dSYM
	rm *.hpp.gch
	rm *.out
	rm *.hpp.*
