#include <iostream>
#include "../include/combat.h"

using namespace std;

void playerTurn();

void enemyTurn(Enemy &e);

//make combat a bool that will return false once it is over.
bool combat(Player &player, vector <Enemy> enemies){

	vector <bool> deadEnemies;
	size_t enemiesDead = 0;
	size_t numEnemies = enemies.size();
	bool playerDead = false;
	bool enemiesDefeated = false;

	deadEnemies.resize(numEnemies);

	cout << "Start combat\n";

	//run the combat loop until either the enemies or the player is dead
	do{

		//check if player is dead
		if(player.hp <= 0){

			playerDead = true;
			break;

		}
		//check how many enemies have died so far
		for(size_t i = 0; i < enemies.size(); i++){

			//if a new enemy has died, add it to the list of dead enemies
			if(enemies[i].hp <= 0 && !deadEnemies[i]){

				enemiesDead++;
				deadEnemies[i] = true;

			}

		}

		//check if all of the enemies are dead
		if(enemiesDead == numEnemies){

			enemiesDefeated = true;
			break;

		}


		//TODO: make turns based off of the player's and enemies' speed, rather than just player first then enemies

		playerTurn();

		for(size_t i = 0; i < enemies.size(); i++){

			if(enemies[i].hp > 0){

				enemyTurn(enemies[i]);

			}

		}


	}while(true);

}

void playerTurn(){

	int action;

	cout << "Player's turn\n";
	cout << "1) Attack\n2) Defend\n3)Items\n4)Run\n";
	cout << "What will you do? ";
	cin >> action;

	switch(action){

		case 1:
			cout << "Player attacked\n";
			break;

		case 2:
			cout << "Player defended\n";
			break;

		case 3:
			cout << "Player used an item\n";
			break;

		case 4:
			cout << "Player tried to run\n";
			break;

		default:
			cout << "invalid action\n";
			break;

	}

}

void enemyTurn(Enemy &e){

	cout << "Enemy's turn\n";
	

}
