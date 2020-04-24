#include <iostream>
#include <random>
#include <ctime>
#include "../include/game.h"

using namespace std;

pair<int, bool> playerTurn(Player *player);

int enemyTurn(Player *player, Enemy *enemy);

//make combat a bool that will return false once it is over.
bool combat(Player *player, Enemy *enemy) {
	int eh = enemy->health;
	//run the combat loop until either the enemies or the player is dead
	while (true) {
		int speed = player->Agility;
		int defence = player->Defense;
		int enemyDamage = enemyTurn(player, enemy);
		pair<int, bool> playerDamage = playerTurn(player);
		if (player->Agility >= enemy->speed) {
			enemy->health -= playerDamage.first*((player->Strength+10.)/10.);
			if (enemy->health <= 0) {
				player->Agility = speed;
				player->Defense = defence;
				enemy->health = eh;
				return true;
				
			}
			if (playerDamage.first != 0) {
				if (playerDamage.second) {
					cout << "You landed a critical hit for " << ceil(playerDamage.first*((player->Strength+10.)/10.)) << " damage! Your opponent now has " << enemy->health << " health remaining!\n";
				}
				else cout << "You landed a hit for " << ceil(playerDamage.first*((player->Strength+10.)/10.)) << " damage! Your opponent now has " << enemy->health << " health remaining!\n";
			}
			else if (!playerDamage.second) cout << "Your attack missed!\n";
			player->Willpower -= enemyDamage*((8.-player->Defense)/8.);
			if (player->Willpower <= 0){enemy->health = eh; return false;}
			if (enemyDamage == 0) cout << "Your opponent's attack missed!\n";
			else cout << "Your opponent hit you for " << ceil(enemyDamage*((8.-player->Defense)/8.)) << " damage! You have " << player->Willpower << " Willpower left!\n";
				
		}
		else {
			player->Willpower -= enemyDamage*((8.-player->Defense)/8.);
			if (player->Willpower <= 0){enemy->health = eh; return false;}
			if (enemyDamage == 0) cout << "Your opponents's attack missed!\n";
			else cout << "Your opponent hit you for " << ceil(enemyDamage*((8.-player->Defense)/8.)) << " damage! You have " << player->Willpower << " Willpower left!\n";
			
			enemy->health -= playerDamage.first*((player->Strength+10.)/10.);
			if (enemy->health <= 0) {
				player->Agility = speed;
				player->Defense = defence;
				enemy->health = eh;
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
		player->Agility = speed;
		player->Defense = defence;
	}
}

pair<int, bool> playerTurn(Player *player) {

	int action, counter, weaponChoice;
	string weapons[6];
	srand(time(NULL));

	cout << "Player's turn\n";
	cout << "1) Attack\n2) Replenish Willpower(hp) (" << player->Courage << " in inventory)\n";
	cout << "What will you do?\n\n";
	
	while (true) {
		
		cin >> action;
		
		if((action != 1)&&(action != 2))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid action, please try again...\n\n";
			continue;
		}
		
		printf("\n");

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
					cout << counter << ") Knife...\n";
					weapons[counter] = "Knife";
				}
				while(true) {
					cin >> weaponChoice;
					if (weaponChoice > 0 && weaponChoice < 5 && weapons[weaponChoice] != "") break;
					else
					{
            			cin.clear();
            			cin.ignore(numeric_limits<streamsize>::max(), '\n');
            			cout << "Invalid action, please try again...\n\n";
            			continue;
					}
				}
				printf("\n");
				if (weapons[weaponChoice] == "Saw") {
					player->Agility = 0;
					int hitChance = 50 + ((player->Accuracy/5.) * 35.);
					if ((rand()%100) <= hitChance) {
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

		else if (action == 2) {
			if (player->Courage > 0) {
				cout << "You look at a picture of your family. Willpower(hp) replenished!\n";
				player->Willpower = 100;
				player->Courage--;
				return make_pair<int, bool>(0, true);
			}
			cout << "You have no Courage, please try another option...\n\n";
			continue;
		}
	}
}

int enemyTurn(Player *player, Enemy *enemy) {
	int hitChance = enemy->accuracy - ((player->Agility/5.) * 40.);
	if ((rand()%100) <= hitChance) {
		return enemy->damage;
	}
	return 0;
}

//int main()
//{
//	return 0;
//}

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
