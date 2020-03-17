CPP= g++
CPPFLAGS= -g -Wall -std=gnu++11
PROG= src/main.cpp src/combat.cpp src/inventory.cpp src/room.cpp
OBJ= $(PROG:.cpp=.o)
HEADERS= /

game : $(OBJ) 
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

clean rm -f $
