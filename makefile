SRC= src/combat.cpp src/inventory.cpp src/play.cpp
OBJ= $(SRC:.cpp=.o)
CPP= g++
CPPFLAGS= -Wall -Wextra -std=gnu++11 -g -O0

all: game

obj/combat.o: src/combat.cpp include/game.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iinclude src/combat.cpp
	
obj/play.o: src/play.cpp include/game.h include/play.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iinclude src/play.cpp

game: $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

clean : 
	rm -f obj/* game
