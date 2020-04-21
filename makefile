SRC= src/main.cpp src/combat.cpp src/inventory.cpp src/room.cpp
OBJ= $(SRC:.cpp=.o)
HEADERS= headers/combat.h headers/inventory.h
CPP= g++
CPPFLAGS= -g -Wall -std=gnu++11

all: game

obj/combat.o: src/combat.cpp headers/combat.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iheaders/combat.h src/combat.cpp

obj/inventory.o: src/inventory.cpp headers/inventory.h
	$(CPP) $(CPPFLAGS) -c -o $@ -Iheaders  src/inventory.cpp

obj/room.o: src/room.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ src/room.cpp

obj/main.o: src/main.cpp 
	$(CPP) $(CPPFLAGS) -c -o $@ src/main.cpp
	
game: $(OBJ) 
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

clean : 
	rm -f obj/* game
