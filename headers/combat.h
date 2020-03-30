#include <vector>
#include <string>

using namespace std;

struct Item{

};

struct Weapon{

};

struct Attack{

	string name;
	int damage;

};

struct Player{

	int hp;
	int willpower;

	vector <Item> items;
	vector <Weapon> weapons;
	vector <Attack> attacks;

	void TakeDamage(int amount);


};

struct Enemy{

	int hp;
	vector<Attack> attacks;
	void TakeDamage(int amount);

};
