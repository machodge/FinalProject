#include <fstream>
#include <iostream>
#include <map>
#include <cmath>
//#include "../headers/inventory.h"
#include "combat.h"
using namespace std;

Items::Items() {
    fstream fin;
    int numModifiers, statInc;
    string stat;
    fin.open(("../data/PassiveItems.txt"));

    //if (fin.fail()) return false;

    while (fin >> numModifiers) {
        PassiveItem item;
        getline(fin, item.name);
        getline(fin, item.description);
        for (int i = 0; i < numModifiers; i++) {
            fin >> stat;

            if(stat == "will") fin >> item.willInc;
            else if(stat == "maxWill") fin >> item.maxWillInc;
            else if(stat == "str") fin >> item.strengthInc;
            else if(stat == "def") fin >> item.defenceInc;
            else if(stat == "agl") fin >> item.agilityInc;
            else if(stat == "acc") fin >> item.accuracyInc;
        }
        pItems.insert(pair<string, PassiveItem>(item.name, item));
    }

    fin.close();
    fin.open("../data/ActiveItems.txt");
    //if (fin.fail()) return false;

    while (fin >> numModifiers) {
        ActiveItem item;
        getline(fin, item.name);
        getline(fin, item.description);
        for (int i = 0; i < numModifiers; i++) {
            fin >> stat;

            if(stat == "dmg") fin >> item.damage;
            else if(stat == "acc") fin >> item.accuracy;
            else if(stat == "spd") fin >> item.speed;
            else if(stat == "crit") fin >> item.critChance;
        }
        aItems.insert(pair<string, ActiveItem>(item.name, item));
    }
}

bool Items::applyItem(string itemName, Player &player) {
    if (pItems.find(itemName) == pItems.end()) return false;
    PassiveItem item = pItems.find(itemName)->second;

    player.accuracy += item.accuracyInc;
    player.agility += item.agilityInc;
    player.defence += item.defenceInc;
    player.strength += item.strengthInc;
    player.maxWillpower += item.maxWillInc;
    
    if (item.willInc == -1) player.willpower = player.maxWillpower;
    else player.willpower += item.willInc;

    if (player.willpower > player.maxWillpower) player.willpower = player.maxWillpower; 

    player.items.push_back(item);

    return true;
}

bool Items::addWeapon(string weaponName, Player &player) {
    if (aItems.find(weaponName) == aItems.end()) return false;
    ActiveItem weapon = aItems.find(weaponName)->second;

    player.weapons.push_back(weapon);

    return true;
}

PassiveItem Items::getItem(string itemName) {
    return pItems.find(itemName)->second;
}

ActiveItem Items::getWeapon(string weaponName) {
    return aItems.find(weaponName)->second;
}

//AttackAccuracy = ln(PlayerAcc*WeaponAcc)*(25/ln(10))
int Items::getAttAccuracy(string weaponName, Player &player) {
    if (aItems.find(weaponName) == aItems.end()) return -1;
    return log(player.accuracy * aItems.find(weaponName)->second.accuracy) * (25./log(10));
}

//AttackSpeed = ((agility/100)+1)*WeaponSpeed
int Items::getAttSpeed(string weaponName, Player &player) {
    if (aItems.find(weaponName) == aItems.end()) return -1;
    return ((((double) player.agility)/100)+1) * (double) aItems.find(weaponName)->second.speed;
}

//AttackDamage = ((strength/100)+1)*WeaponDamage
int Items::getAttDmg(string weaponName, Player &player) {
    if (aItems.find(weaponName) == aItems.end()) return -1;
    return ((((double) player.strength)/100)+1) * (double) aItems.find(weaponName)->second.damage;
}
