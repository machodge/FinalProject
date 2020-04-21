SRC= src/main.cpp src/combat.cpp src/inventory.cpp src/room.cpp
OBJ= $(SRC:.cpp=.o)
HEADERS= headers/combat.h headers/inventory.h
CPP= g++
CPPFLAGS= -Wall -Wextra -std=gnu++11

all: game

obj/combat.o: src/combat.cpp include/combat.h
	$(CPP) $(CPPFLAGS) -Iinclude -c -o obj/combat.o src/combat.cpp

obj/inventory.o: src/inventory.cpp include/inventory.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iinclude src/inventory.cpp

obj/room.o: src/room.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ src/room.cpp

obj/main.o: src/main.cpp 
	$(CPP) $(CPPFLAGS) -c -o $@ src/main.cpp
	
game: $(OBJ) 
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

clean : 
	rm -f obj/* game
