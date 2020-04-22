SRC= combat.cpp inventory.cpp play.cpp
OBJ= $(SRC:.cpp=.o)
CPP= g++
CPPFLAGS= -Wall -Wextra -std=gnu++11

all: game

combat.o: combat.cpp combat.h
	$(CPP) $(CPPFLAGS) -c -o $@ combat.cpp
	
play.o: play.cpp game.h
	$(CPP) $(CPPFLAGS) -c -o $@ play.cpp

game: $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)

clean : 
	rm *.o game
