#include "combat.cpp"
#include "inventory.cpp"

struct Player{

	int health;
	int willpower;

	vector <Items> items;
	vector <Weapons> weapons;

	vector <Attacks> attacks;

};
