SRC= src/combat.cpp src/inventory.cpp src/play.cpp
OBJ= $(SRC:.cpp=.o)
CPP= g++
CPPFLAGS= -Wall -Wextra -std=gnu++11

all: game

obj/combat.o: src/combat.cpp include/combat.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iinclude src/combat.cpp

obj/inventory.o: src/inventory.cpp include/inventory.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iinclude src/inventory.cpp
	
obj/play.o: src/play.cpp game.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iinclude src/play.cpp

game: $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

clean : 
	rm -f obj/* game
