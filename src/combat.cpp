//Code for the combat system
#include <iostream>
#include <random>
#include <ctime>
#include "../include/game.h"

using namespace std;

pair<int, bool> playerTurn(Player *player);

int enemyTurn(Player *player, Enemy *enemy);

//start combat, returns a bool that is false if you lose and true if you win
bool combat(Player *player, Enemy *enemy) {

	//run the combat loop until either the enemies or the player is dead
	while (true) {
		//keeps the stats that can be changed by weapons so that we can return them to normal
		int speed = player->Agility;
		int defence = player->Defense;
		int enemyDamage = enemyTurn(player, enemy); //gets the damage the enemy will do
		pair<int, bool> playerDamage = playerTurn(player); //gets the damage the player will do
		
		//if the players agility is higher than the enemy's speed they go first
		if (player->Agility >= enemy->speed) {
			//deals damage to the enemy with strength multiplyer
			enemy->health -= playerDamage.first*((player->Strength+10.)/10.); 
			
			//if the enemy dies exit combat
			if (enemy->health <= 0) {
				player->Agility = speed;
				player->Defense = defence;
				return true;	
			}
			
			//if damage is not 0, print how much damage was delt
			if (playerDamage.first != 0) {
				//if its a crit, print that you landed a crit
				if (playerDamage.second) {
					cout << "You landed a critical hit for " << ceil(playerDamage.first*((player->Strength+10.)/10.)) << " damage! Your opponent now has " << enemy->health << " health remaining!\n";
				}
				//print you landed a non-critical hit
				else cout << "You landed a hit for " << ceil(playerDamage.first*((player->Strength+10.)/10.)) << " damage! Your opponent now has " << enemy->health << " health remaining!\n";
			}
			//prints you missed if you do 0 damage and don't heal
			else if (!playerDamage.second) cout << "Your attack missed!\n";
			
			//deals damage to player based off their defense
			player->Willpower -= enemyDamage*((8.-player->Defense)/8.);
			if (player->Willpower <= 0) return false; //exit combat if you die
			
			//if your opponent does 0 damage, output that they missed
			if (enemyDamage == 0) cout << "Your opponent's attack missed!\n";
			//print the amount of damage you took
			else cout << "Your opponent hit you for " << ceil(enemyDamage*((8.-player->Defense)/8.)) << " damage! You have " << player->Willpower << " Willpower left!\n";
				
		}
		//the enemy goes first, the code is the same as the last block but with the order switched
		else {
			player->Willpower -= enemyDamage*((8.-player->Defense)/8.);
			if (player->Willpower <= 0) return false;
			if (enemyDamage == 0) cout << "Your opponents's attack missed!\n";
			else cout << "Your opponent hit you for " << ceil(enemyDamage*((8.-player->Defense)/8.)) << " damage! You have " << player->Willpower << " Willpower left!\n";
			
			enemy->health -= playerDamage.first*((player->Strength+10.)/10.);
			if (enemy->health <= 0) {
				player->Agility = speed;
				player->Defense = defence;
				return true;
			}
			if (playerDamage.first != 0) {
				if (playerDamage.second) {
					cout << "You landed a critical hit for " << ceil(playerDamage.first*((player->Strength+10.)/10.)) << " damage! Your opponents now has " << enemy->health << " health remaining!\n";
				}
				else cout << "You landed a hit for " << ceil(playerDamage.first*((player->Strength+10.)/10.)) << " damage! Your opponent now has " << enemy->health << " health remaining!\n";
			}
			else if (!playerDamage.second) cout << "Your attack missed!\n";
		}
		//returns players stats to baseline after the turn
		player->Agility = speed;
		player->Defense = defence;
	}
}

//function for players turn returns a pair where the first is damage and the second is a bool that is true if you get
//a crit, an output of {0, true} represents a heal.
pair<int, bool> playerTurn(Player *player) {

	int action, counter, weaponChoice;
	string weapons[6];
	srand(time(NULL));

	//outputs possible actions
	cout << "Player's turn\n";
	cout << "1) Attack\n2) Heal (" << player->Courage << " in inventory)\n";
	cout << "What will you do?\n";
	
	while (true) {
		cin >> action;

		//if they attack, build the players weapon list and print what weapons are avalable and what their stats are
		if (action == 1) {
			if (player->DOG || player->BoneSaw || player->Scalpel || player->Scythe || player->Knife) {
				counter = 1;
				cout << "What weapon will you use?\n";
				if (player->BoneSaw) {
					cout << counter << ") Accomplice's Bone Saw: Accuracy is " << floor(50 + ((player->Accuracy/5.) * 35.)) << "%, Damage is " << ceil(30*((player->Strength+10.)/10.)) << endl;
					weapons[counter] = "Saw";
					counter++;
				}
				if (player->Scythe) {
					cout << counter << ") Harvester's Scythe: Accuracy is " << floor(60 + ((player->Accuracy/5.) * 35.)) << "%, Damage is " << ceil(20*((player->Strength+10.)/10.)) << ", High Crit Chance\n";
					weapons[counter] = "Scythe";
					counter++;
				}
				if (player->DOG) {
					cout << counter << ") Delusion Of Grandeur: Accuracy is " << floor(40 + ((player->Accuracy/5.) * 25.)) << "%, Damage is " << ceil(15*((player->Strength+10.)/10.)) << ", Increased Defence\n";
					weapons[counter] = "DOG";
					counter++;
				}
				if (player->Scalpel) {
					cout << counter << ") Old Spaniard's Scalpel: Accuracy is " << floor(50 + ((player->Accuracy/5.) * 25.)) << "%, Damage is " << ceil(25*((player->Strength+10.)/10.)) << ", Increased Agility\n";
					weapons[counter] = "Scalpel";
					counter++;
				}
				if (player->Knife) {
					cout << counter << ") The Knife...\n";
					weapons[counter] = "Knife";
				}
				//read in the players weapon choice until they pick a valid weapon
				while(true) {
					cin >> weaponChoice;
					if (weaponChoice > 0 && weaponChoice < 5 && weapons[weaponChoice] != "") {
						cin.clear();
						break;
					}
					else cout << "Invalid action, please try again\n";
				}
				
				if (weapons[weaponChoice] == "Saw") {
					player->Agility = 0; //reduces players agility while using this weapon
					int hitChance = 50 + ((player->Accuracy/5.) * 35.); //calculates hit chance based on accuracy
					//rolls to see if a hit
					if ((rand()%100) <= hitChance) {
						//rolls to see if a crit
						if ((rand()%100) < 10) {
							return make_pair<int, bool>(60, true);
						}
						return make_pair<int, bool>(30, false);
					}
					else return make_pair<int, bool>(0, false);
				}
				else if (weapons[weaponChoice] == "Scythe") {
					int hitChance = 60 + ((player->Accuracy/5.) * 35.);
					if ((rand()%100) <= hitChance) {
						if ((rand()%100) < 30) {
							return make_pair<int, bool>(40, true);
						}
						return make_pair<int, bool>(20, false);
					}
					else return make_pair<int, bool>(0, false);
				}
				else if (weapons[weaponChoice] == "DOG") {
					player->Agility = 0;
					player->Defense += 2;
					int hitChance = 40 + ((player->Accuracy/5.) * 25.);
					if ((rand()%100) <= hitChance) {
						if ((rand()%100) < 15) {
							return make_pair<int, bool>(30, true);
						}
						return make_pair<int, bool>(15, false);
					}
					else return make_pair<int, bool>(0, false);
				}
				else if (weapons[weaponChoice] == "Scalpel") {
					player->Agility += 2;
					int hitChance = 50 + ((player->Accuracy/5.) * 25.);
					if ((rand()%100) <= hitChance) {
						if ((rand()%100) < 25) {
							return make_pair<int, bool>(50, true);
						}
						return make_pair<int, bool>(25, false);
					}
					else return make_pair<int, bool>(0, false);
				}
				else if (weapons[weaponChoice] == "Knife") {
					player->Agility = 6;
					player->Defense = 7;
					return make_pair<int, bool>(50, false);
				}
			}
			//if the player has no weapons, use fists automatically
			else {
				int hitChance = 60 + ((player->Accuracy/5.) * 25.);
				if ((rand()%100) <= hitChance) {
					if ((rand()%100) < 15) {
						return make_pair<int, bool>(20, true);
					}
					return make_pair<int, bool>(10, false);
				}
				else return make_pair<int, bool>(0, false);
			}
		}

		//heals the player to 100% health, this will always be done before enemy attacks
		else if (action == 2) {
			if (player->Courage > 0) {
				cout << "You Willpower has been restored!\n";
				player->Willpower = 100;
				player->Courage--;
				return make_pair<int, bool>(0, true);
			}
			//if the player has no courage in their inventory then they can't heal
			cout << "You have no Courage, please try another option...\n";
			continue;
		}

		//if the player does an invalid action print this
		else {
			cout << "invalid action, please try again...\n";
			cin.clear();
		}
	}
}

//the enemy turn is pretty simple since they have only one attack
int enemyTurn(Player *player, Enemy *enemy) {
	//calculates hit chance based on the enemys accuracy and the players agility
	int hitChance = enemy->accuracy - ((player->Agility/5.) * 40.);
	//rolls for a hit, otherwise return 0
	if ((rand()%100) <= hitChance) {
		return enemy->damage;
	}
	return 0;
}

//main function for debuging combat
/*int main() {
	Player *player = new Player;
	Enemy *enemy = new Enemy; 
	player->Courage = 5;
	player->Willpower = 100;
	player->Strength = 0;
	player->Agility = 5;
	player->Accuracy = 5;
	player->Defense = 2;
	player->BoneSaw = true;
	player->Scythe = true;
	player->DOG = false;
	player->Scalpel = true;
	player->Knife = false;
	
	enemy->health = 100;
	enemy->damage = 10;
	enemy->accuracy = 90;
	enemy->speed = 1;
	
	combat(player, enemy);
	
	return 0;
}*/