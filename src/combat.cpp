#include <iostream>
#include <random>
#include <ctime>
//#include "../include/combat.h"
#include "game.h"

using namespace std;

pair<int, bool> playerTurn(Player &player, Enemy &enemy);

int enemyTurn(Player &player, Enemy &enemy);

//make combat a bool that will return false once it is over.
bool combat(Player &player, Enemy &enemy) {

	//run the combat loop until either the enemies or the player is dead
	while (true) {
		Player oldPlayer = player;
		int enemyDamage = enemyTurn(player, enemy);
		pair<int, bool> playerDamage = playerTurn(player, enemy);
		if (player.Agility < enemy.speed) {
			enemy.health -= playerDamage.second*((player.Strength+10)/10);
			if (enemy.health <= 0) return true;
			if (playerDamage.first != 0) {
				if (playerDamage.second) {
					cout << "You landed a critical hit for " << playerDamage.first << " damage! The enemy now has " << enemy.health << "health remaining!\n";
				}
				else cout << "You landed a hit for " << playerDamage.first << " damage! The enemy now has " << enemy.health << "health remaining!\n";
			}
			else cout << "Your attack missed!";
			player.Willpower -= enemyDamage*((7-player.Defense)/7);
			if (player.Willpower <= 0) return false;
			if (enemyDamage == 0) cout << "The enemy's attack missed!";
			else cout << "Your opponent hit you for " << enemyDamage << " damage! You have " << player.Willpower << " Willpower left!";
			
		}
		else {
			player.Willpower -= enemyDamage*((7-player.Defense)/7);
			if (player.Willpower <= 0) return false;
			if (enemyDamage == 0) cout << "The enemy's attack missed!";
			else cout << "Your opponent hit you for " << enemyDamage << " damage! You have " << player.Willpower << " Willpower left!";
			
			enemy.health -= playerDamage.second*((player.Strength+10)/10);
			if (enemy.health <= 0) return true;
			if (playerDamage.first != 0) {
				if (playerDamage.second) {
					cout << "You landed a critical hit for " << playerDamage.first << " damage! The enemy now has " << enemy.health << "health remaining!\n";
				}
				else cout << "You landed a hit for " << playerDamage.first << " damage! The enemy now has " << enemy.health << "health remaining!\n";
			}
			else cout << "Your attack missed!";
		}
	}
}

pair<int, bool> playerTurn(Player &player) {

	int action, counter, weaponChoice;
	string weapons[6];
	srand(time(NULL));

	cout << "Player's turn\n";
	cout << "1) Attack\n2) Heal (" << player.Courage << " in inventory\n";
	cout << "What will you do?\n";
	cin >> action;

	if (action == 1) {
		if (player.DOG || player.BoneSaw || player.Scalpel || player.Scythe) {
			counter = 1;
			cout << "What weapon will you use?\n";
			if (player.BoneSaw) {
				cout << counter << ") Accomplice's Bone Saw: High Strength, Low Agility\n";
				weapons[counter] = "Saw";
				counter++;
			}
			if (player.Scythe) {
				cout << counter << ") Harvester's Scythe: High Accuracy, Medium Strength\n";
				weapons[counter] = "Scythe";
				counter++;
			}
			if (player.DOG) {
				cout << counter << ") Delusion Of Grandeur: High Defense, Medium Strength, Low Agility\n";
				weapons[counter] = "DOG";
				counter++;
			}
			if (player.Scalpel) {
				cout << counter << ") Old Spaniard's Scalpel: High Agility, Medium Accuracy, Medium Strength\n";
				weapons[counter] = "Scalpel";
			}
			if (player.Knife) {
				cout << counter << ") The Knife: Very High Speed, Damamage, and Accuracy\n";
				weapons[counter] = "Knife";
			}
			while(true) {
				cin >> weaponChoice;
				if (weaponChoice > 0 && weaponChoice < 5 && weapons[weaponChoice] != "") break;
				else cout << "Invalid action, please try again\n";
			}
			if (weapons[weaponChoice] == "Saw") {
				player.Agility = 0;
				int hitChance = 50 + ((player.Accuracy/5) * 35);
				if ((rand()%100) <= hitChance) {
					if ((rand()%100) < 10) {
						return make_pair<int, bool>(60, true);
					}
					return make_pair<int, bool>(30, false);
				}
				else return make_pair<int, bool>(0, false);
			}
			else if (weapons[weaponChoice] == "Scythe") {
				int hitChance = 60 + ((player.Accuracy/5) * 35);
				if ((rand()%100) <= hitChance) {
					if ((rand()%100) < 30) {
						return make_pair<int, bool>(40, true);
					}
					return make_pair<int, bool>(20, false);
				}
				else return make_pair<int, bool>(0, false);
			}
			else if (weapons[weaponChoice] == "DOG") {
				player.Agility = 0;
				player.Defense += 2;
				int hitChance = 40 + ((player.Accuracy/5) * 25);
				if ((rand()%100) <= hitChance) {
					if ((rand()%100) < 15) {
						return make_pair<int, bool>(30, true);
					}
					return make_pair<int, bool>(15, false);
				}
				else return make_pair<int, bool>(0, false);
			}
			else if (weapons[weaponChoice] == "Scalpel") {
				player.Agility = 10;
				int hitChance = 50 + ((player.Accuracy/5) * 25);
				if ((rand()%100) <= hitChance) {
					if ((rand()%100) < 25) {
						return make_pair<int, bool>(50, true);
					}
					return make_pair<int, bool>(25, false);
				}
				else return make_pair<int, bool>(0, false);
			}
			else if (weapons[weaponChoice] == "Knife") {
				player.Agility = 10;
				player.Defense = 7;
				return make_pair<int, bool>(50, false);
			}
		}
		else {
			int hitChance = 60 + ((player.Accuracy/5) * 25);
			if ((rand()%100) <= hitChance) {
				if ((rand()%100) < 15) {
					return make_pair<int, bool>(20, true);
				}
				return make_pair<int, bool>(10, false);
			}
			else return make_pair<int, bool>(0, false);
		}
	}

	else if (action == 2) {
		cout << "Player used an item\n";
	}

	else {
		cout << "invalid action\n";
	}

}

int enemyTurn(Player &player, Enemy &enemy) {
	int hitChance = enemy.accuracy - ((player.Agility/5) * 40);
	if ((rand()%100) <= hitChance) {
		return enemy.damage;
	}
	return 0;
}
