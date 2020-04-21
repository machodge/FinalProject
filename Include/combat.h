#ifndef COMBAT_H
#define COMBAT_H
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Player;

struct PassiveItem {
    string name;
    string description;
    int willInc = 0;        //amount an item increases willpower, -1 means return to max
    int maxWillInc = 0;
	int strengthInc = 0;    //amount an item increases strength by
    int defenceInc = 0;     //amount an item increases defence by
    int agilityInc = 0;     //amount an item increases agility by
    int accuracyInc = 0;    //amount an item increases accuracy by
};

//formulas for how player stats interact with weapon stats, the accuracy one is a little weird, might need some work
//AttackAccuracy = ln(PlayerAcc*WeaponAcc)*(25/ln(10))
//AttackSpeed = ((agility/100)+1)*WeaponSpeed
//AttackDamage = ((strength/100)+1)*WeaponDamage
struct ActiveItem {
    string name;
    string description;
    int damage;     //how much damage a successfull hit does, if a crit is rolled damage is doubled
    int accuracy;   //0-100, a number is rolled between 0 and 100, any number lower than
                    //accuracy is a hit, critChance is then rolled
    int speed;      //the speed determines turn order, agility is used as a multiplier for this
    int critChance; //0-100, a number between 0 and 100 is rolled and results 
                    //in a crit for any number less than this number
};

class Items {
public:
    Items();
    bool applyItem(string itemName, Player &player);
    bool addWeapon(string weaponName, Player &player);
    PassiveItem getItem(string itemName);
    ActiveItem getWeapon(string weaponName);
	int getAttAccuracy(string weaponName, Player &player);
	int getAttSpeed(string weaponName, Player &player);
	int getAttDmg(string weaponName, Player &player);
private:
    map<string, PassiveItem> pItems;
    map<string, ActiveItem> aItems;
};

struct Player{

	int maxWillpower;
	int willpower;
	int strength;
	int defence;
	int agility;
	int accuracy;

	vector <PassiveItem> items;
	vector <ActiveItem> weapons;

	void TakeDamage(int amount);


};

struct Enemy{

	int hp;
	vector<Attack> attacks;
	void TakeDamage(int amount);

};

#endif
