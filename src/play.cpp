#include "../include/game.h"
#include "../include/play.h"
#include<algorithm>
#include<iostream>
#include<stdlib.h>
#include<sstream>
#include<fstream>
#include<vector>
#include<time.h>
#include<map>

using namespace std;

void read_in(vector<vector<Room *>> &f, ifstream &fin);			//Prototype to read in rooms
void adj_list(vector<vector<Room *>> &f);						//Prototype to create adjacency lists
void clean(vector<vector<Room *>> &f);							//Prototype to free allocated data
void clean_m(vector<Enemy *> &mobs);							//Prototype to free allocated data
bool spawn(int i, int j, int cf);								//Prototype to check if area allows enemy spawn
bool game_stage(int gs);										//Prototype that roles for a chance to start combat
Enemy* renemy(vector<Enemy *> mobs, int gs);					//Prototype to return a random enemy
void raise_stat(vector<Enemy *> &mobs);							//Prototype to raise enemy stats

int main()
{
	map<string, Action*>::iterator sit;		//Action iterator
	vector<vector<Room *> > f, f1, f2;		//Game map
	map<string, Room *>::iterator nit;		//Map iterator
	int d, gs, cf, row, col, r;				//Variables to keep track of game progress
	vector<Enemy *> mobs;					//Vector of enemy types
	stringstream ss;						//Stringstream for data read in
	string line, cd;						//Strings to read in data
	ifstream fin;							//File in to read from file
	Player *p;								//Pointer to the player class								
	int i, j;								//Variables for game progression

//Allocating memory to the player
	p = new Player;
//Checks for saved games, error checks accordingly, then opens and reads from proper file
    printf("Welcome to Insomnia. (Press enter to continue)");
    cin.get();
	printf("\n");

	printf("Type \"NG\" to start a New Game or \"LS\" to Load a Saved game.\n\n");
	cin >> cd;
	
	while((cd != "LS")&&(cd != "NG"))
	{
		printf("Invalid input.\n\n");
		cin >> cd;
	}
	
	if(cd == "LS")
	{
		fin.open("data/save.txt");
		getline(fin, line);
		ss.clear();
		ss.str(line);
		//Checks wheter or not save contains data.
		if(line.empty())
		{
			printf("Saved game not found, starting a new game.\n\n");
			cd = "NG";
			fin.close();
		}
		else
		{
			//If save contains data, reads in the game state and player data
			ss >> gs >> cf >> row >> col >> d >> r;
			getline(fin, line);
		    ss.clear();
	        ss.str(line);
		    ss >> p->Courage >> p->Willpower >> p->Strength >> p->Agility >> p->Accuracy >> p->Defense
			   >> p->Death >> p->BoneSaw >> p->Scythe >> p->DOG >> p->Scalpel >> p->Knife;
		}
	}
    
	//If new game reads in default gamestate and player data
	if(cd == "NG")
	{
		fin.open("data/game.txt");
		getline(fin, line);
		ss.clear();
		ss.str(line);
		ss >> gs >> cf >> row >> col >> d >> r;
		getline(fin, line);
		ss.clear();
		ss.str(line);
		ss >> p->Courage >> p->Willpower >> p->Strength >> p->Agility >> p->Accuracy >> p->Defense
		   >> p->Death >> p->BoneSaw >> p->Scythe >> p->DOG >> p->Scalpel >> p->Knife;
		//Asks a question that boosts one stat
		slow_print("How would you describe yourself?\n", 30);
		slow_print("Paranoid(Type 'p'), Fearful(Type 'f'), Delusional(Type 'd'), Brave(Type 'c'), or Stable(Type 's')?\n", 30);
		cin >> cd;
		while((cd != "p")&&(cd != "f")&&(cd != "d")&&(cd != "c")&&(cd != "s"))
		{
			printf("Invalid input.\n");
			cin >> cd;
		}
		if(cd == "p")
		{
			p->Accuracy += 1;
			slow_print("You've been gifted paranoia, accuracy increased!\n\n", 30);
		}
		else if(cd == "f")
		{
			p->Agility += 1;
			slow_print("You've been gifted fear, agility increased!\n\n", 30);
		}
		else if(cd == "d")
		{
			p->Strength += 1;
			slow_print("You've been gifted delusion, strength increased!\n\n", 30);
		}
		else if(cd == "c")
		{
			p->Courage += 1;
			slow_print("You've been gifted courage, you can use this to increase your willpower(hp).\n\n", 30);
		}
		else if(cd == "s")
		{
			p->Defense += 1;
			slow_print("You've been gifted stability, defense increased!\n\n", 30);
		}
		//First line of game
		slow_print("You wake up in a white bed, it's still night out.\n\n", 30);
	}
    
//Prints out player options
	printf("Type one of the cardinal directions (lowercase) to move.\n");
    printf("Type 'i' (Info) to view your willpower (health) and your current stats.\n");
    printf("Type ‘a’ (Actions) to view current actions you can take.\n");
    printf("Type 'l' (Look) to see the description of your surrounding location.\n");
	printf("Type 'h' (Heal) to use courage and replenish your willpower.\n");
    printf("Type 'S' (Save) to save your game.\n");
    printf("Type 'q' (Quit) to quit the game.\n");
    printf("Type 'o' (Options) to see these options again.\n\n");

//Creates enemies
    make_enemy(mobs, fin);
//Makes rooms from read in file
	read_in(f1, fin);
	read_in(f2, fin);

//Closes file
	fin.close();

//Creates adjacency lists
	adj_list(f1);
	adj_list(f2);	

//Initializes starting area depending on read in data
	i = row;
	j = col;
	if(cf == 1)
		f = f1;
	else
		f = f2;
	
//Takes input from user and plays game
	cin.get();
	while(1)
	{
		//Formatting for mid-game scene
		if(r != -1)
			r++;
		//Takes user input
		getline(cin, line);
		printf("\n");
		//Quits game if input is q
		if(line == "q")
		{
			printf("Are you sure you want to exit the game?(y/n)\n");
			cin >> cd;
			cin.get();
			while((cd != "y")&&(cd != "n"))
			{
				printf("Invalid input.\n");
				cin >> cd;
			}
			if(cd == "y")
				break;
			printf("\n");
		}
		//Mid-game scene
		else if(r == 4)
		{
			r = -1;
			slow_print("...", 100);
			cin.get();
			slow_print("\"Something feels off...\"", 100);
			cin.get();
			slow_print("\"I guess he got m-\"\n", 100);
			slow_print("...", 100);
			cin.get();
			slow_print("You wake up in a white bed, it's still night out.\n\n", 30);
			i = 0;
			j = 0;
			gs++;
			raise_stat(mobs);
		}
		//Pre-endgame scene
		else if((i == 2)&&(j == 0)&&(cf == 1)&&(gs == 4)&&(line == "n"))
		{
			sit = f1[i][j]->actions.find("Talk to the man");
			if(sit->second->check)
			{
				slow_print("As you go to leave the man gets up and charges at you.", 30);
				cin.get();
				slow_print("You feel something sharp jab you and your vision begins to blur again.", 30);
				cin.get();
				slow_print("...", 100);
				cin.get();
				slow_print("You wake up in a white bed, it's still night out.", 30);
				cin.get();
				slow_print("On the dresser next to you is a knife with a note.\n", 30);
				slow_print("\"Earn your truth.\"", 30);
				cin.get();
				slow_print("You pick up the knife.\n\n", 30);
				p->Scalpel = false;
				p->DOG = false;
				p->BoneSaw = false;
				p->Scythe = false;
				p->Knife = true;
				i = 0;
				j = 0;
				gs++;
				raise_stat(mobs);
			}
			else
			{
				i = 1;
				j = 0;
				printf("%s\n\n", f[i][j]->description.c_str());
			}
		}
		//If user inputs an action
		else if(f[i][j]->actions.find(line) != f[i][j]->actions.end())
		{
			//Sets sit to that action
			sit = f[i][j]->actions.find(line);
			//Error checks if action has already been done
			if((sit->second->check)&&(sit->second->item != "None"))
				slow_print("Action already explored.\n\n", 30);
			//If not, preforms action
			else
			{
				//If action gives you an item, act accordingly 
				if(sit->second->item == "Courage")
					p->Courage++;
				else if(sit->second->item == "Fear")
					p->Agility++;
				else if(sit->second->item == "Paranoia")
					p->Accuracy++;
				else if(sit->second->item == "Delusion")
					p->Strength++;
				else if(sit->second->item == "Stability")
					p->Defense++;
				else if(sit->second->item == "Harvester's-Scythe")
					p->Scythe = true;
				else if(sit->second->item == "Old-Spaniard's-Scalpel")
					p->Scalpel = true;
				else if(sit->second->item == "Accomplice's-Bone-Saw")
					p->BoneSaw = true;
				else if(sit->second->item == "Delusion-Of-Grandeur")
					p->DOG = true;
				//Else if action is a key, checks if key leads to double doors or another floor and
				//unlocks doors accordingly
				if(sit->second->lock.first != -1)
				{
					if((sit->second->lock.first == 0)&&(sit->second->lock.second == 3))
					{
						f[0][3]->lock = true;
						f[5][3]->lock = true;
					}
					else if((sit->second->lock.first == 3)&&(sit->second->lock.second == 2))
					{
						f[3][2]->lock = true;
						f[4][2]->lock = true;
					}
					else if((sit->second->lock.first == 3)&&(sit->second->lock.second == 7))
					{
						f[3][7]->lock = true;
						f[4][7]->lock = true;
					}
					else if((sit->second->lock.first == 0)&&(sit->second->lock.second == 2))
						f1[0][2]->lock = true;
					else if((sit->second->lock.first == 2)&&(sit->second->lock.second == 0))
						f1[2][0]->lock = true;
					else
						f[sit->second->lock.first][sit->second->lock.second]->lock = true;
				}
				//Print out action description
				slow_print(sit->second->description, 30);
				printf("\n");
				//If action has special dialogue associated with it, outputs dialogue
				if((i == 0)&&(j == 0)&&(!sit->second->check)&&(line == "Search Dresser")&&(cf == 1))
					slow_print("\"Find your truth.\"\n", 55);
				else if((i == 0)&&(j == 7)&&(line == "Search Cabinet")&&(cf == 1))
				{
					printf("April 04: Today me and daddy went to get ice cream. Mom was too busy to come but me and daddy still\n");
					printf("had fun. A mean doggy tried to eat me but daddy saved me. It was scary. I hope we do something fun\n");
					printf("agin tomorrow.");
					cin.get();
					printf("\n");
					if(!sit->second->check)
					{
						slow_print("\"Don't worry sweety, daddy's gonna find you.\"", 55);
						cin.get();
						slow_print("\"We'll be together forever.\"", 55);
						cin.get();
					}
					else
					{
						slow_print("\"Together forever.\"", 55);
						cin.get();
					}
				}
				else if((i == 1)&&(j == 4)&&(cf == 1)&&(!sit->second->check)&&(line == "Look at painting"))
					slow_print("You found paranoia, accuracy increased!\n", 30);
				else if((i == 5)&&(j == 6)&&(cf == 1)&&(line == "Sit Down"))
				{
					printf("(Press enter to get up)");
					cin.get();
				}
				else if((i == 2)&&(j == 0)&&(cf == 1)&&(line == "Talk to the man"))
				{
					if(!sit->second->check)
					{
						slow_print("\"But if I did do it, they’d know.\"", 30);
						cin.get();
						slow_print("\"Oh-ho-ho, they’d know alright!\"", 30);
						cin.get();
						slow_print("\"They’d know what I cannot know which makes them the thing that’ll break me.\"\n", 30);
						slow_print("\"So, will they break me?\"", 40);
						cin.get();
						slow_print("\"Will they break you?\"", 50);
						cin.get();
						slow_print("\"Find your truth.\"", 55);
						cin.get();
						slow_print("The man gives me a key; doctors office is now accessible.\n", 30);
					}
					else
					{
						slow_print("\"Find your truth.\"", 55);
						cin.get();
					}
				}
				else if((i == 2)&&(j == 0)&&(cf == 1)&&(line == "Search Room"))
				{
					printf("April 21: I wonder if mom and daddy will be happy agin. They hav been fighting a lot. They where just\n");
					printf("fighting but now mom is quiet. Daddy is still talking. Hes saying he didnt do it. I hope he didnt do\n");
					printf("to mom what he did to that dog. Hes coming. No matter what I love my daddy verrrryyy mu-");
					cin.get();
					printf("\n");
					if(!sit->second->check)
					{
						slow_print("\"Oh Cindy...\"", 100);
						cin.get();
						slow_print("\"Don't worry sweety, we'll be one big happy family again.\"", 55);
						cin.get();
						slow_print("\"When I get done with the doctor, I'll take you and mom and we can go home.\"", 55);
						cin.get();
						slow_print("\"We'll be-\"", 55);
						cin.get();
						slow_print("A tear leaves your eye.\n", 30);
						slow_print("\"Together... forever...\"", 100);
						cin.get();
					}
					else
					{
						slow_print("\"Together... forever...\"", 100);
						cin.get();
					}
				}
				else if((i == 2)&&(j == 1)&&(cf == 1)&&(line == "Search Room"))
				{
					printf("April 11: Mom stil wont come out with me and daddy. She says I shuldnt also but why not? Daddy is scary\n");
					printf("at times but hes nice, he loves us verrrryyy much. Mom must be tyrd from work. I braut her a gift back\n");
					printf("she was happy.");
					cin.get();
					printf("\n");
					if(!sit->second->check)
					{
						slow_print("\"Mom was just confused, don't worry, we'll all be happy together when I find you.\"\n", 40);
						slow_print("\"Wait for me Cindy.\"", 40);
						cin.get();
					}
					else
					{
						slow_print("\"Wait for me Cindy.\"", 40);
						cin.get();
					}
				}
				else if((i == 3)&&(j == 0)&&(cf == 1)&&(line == "Search Desk"))
				{
					printf("Alan Brown truly is an interesting subject. I have never seen anything like his condition. Schizophrenia\n");
					printf("developing into psychosis is common but such a severe case of it is truly remarkable. He somehow keeps\n");
					printf("finding a way out of his room at night, during that time though he constantly fights the air and murmurs\n");
					printf("to himself. Sometimes he will invade the other patient’s rooms, but he does not even see them, he\n");
					printf("completely looks through them at something else. Of course, before day breaks, I find him, sedate him,\n");
					printf("and take him back to his room, sometimes I would find him passed out. I know what I am doing is widely\n");
					printf("considered malpractice, but I believe he is truly close to seeing past his delusions. I predict if he stays\n");
					printf("on his current path he might come to peace with his demons and cure himself, so for now, I will just keep\n");
					printf("observing him. One thing that continues to shock me, however, is the fact that he has enough courage to keep\n");
					printf("looking at that picture of his family, he cries every time.");
					cin.get();
				}
				else if((i == 3)&&(j == 1)&&(cf == 1)&&(line == "Search Desk"))
				{
					printf("Dr. Graham has lost his damn mind, his fixation with that patient is going to be our downfall. Honestly, I\n");
					printf("do not care if the fool gets himself killed believing in a delusional man, but I will not die with him. Ever\n");
					printf("since his failure a couple of years back he has been dead set on rehabilitating a patient who has past far\n");
					printf("beyond the walls of sanity. The fool truly believes he can do it too. If this gets too out of hand, I will put\n");
					printf("an end to it and call the cops on both, the fool and his broken toy.");
					cin.get();
				}
				else if((i == 3)&&(j == 3)&&(cf == 1)&&(line == "Search Plant"))
					slow_print("You found courage; you can use this to increase your willpower(hp).\n", 30);
				else if((i == 3)&&(j == 4)&&(cf == 1)&&(line == "Take Shower"))
					slow_print("You found courage; you can use this to increase your willpower(hp).\n", 30);
				else if((i == 3)&&(j == 6)&&(cf == 1)&&(line == "Read Note"))
				{
					slow_print("The note reassures you.", 30);
					cin.get();
					slow_print("You found stability; defense increased!\n", 30);
				}
				else if((i == 3)&&(j == 7)&&(cf == 1)&&(line == "Search Stalls"))
					slow_print("You found courage; you can use this to increase your willpower(hp).\n", 30);
				else if((i == 5)&&(j == 4)&&(cf == 1)&&(line == "Turn off tv"))
					slow_print("You found courage; you can use this to increase your willpower(hp).\n", 30);
				else if((i == 5)&&(j == 5)&&(cf == 1)&&(line == "Talk"))
					slow_print("You found courage; you can use this to increase your willpower(hp).\n", 30);
				else if((i == 5)&&(j == 5)&&(cf == 1)&&(line == "Talk?"))
					slow_print("You found delusion; strength increased!\n", 30);
				else if((i == 0)&&(j == 4)&&(cf == 2)&&(line == "Check Cabinets"))
				{
					slow_print("You found a key; kitchen is now accessible.", 30);
					cin.get();
					slow_print("\"You know what?\"", 40);
					cin.get();
					slow_print("\"I actually am hungry, I think I'll do just that!\"\n", 40);
				}
				else if((i == 0)&&(j == 6)&&(cf == 2)&&(line == "Sit at table"))
					slow_print("You found courage; you can use this to increase your willpower(hp).\n", 30);
				else if((i == 1)&&(j == 0)&&(cf == 2)&&(line == "Sit in chair"))
					slow_print("You found stability; defense increased!\n", 30);
				else if((i == 1)&&(j == 6)&&(cf == 2)&&(line == "Check out menu"))
				{
					slow_print("\"Today's menu is\"", 40);
					cin.get();
					slow_print("...", 100);
					cin.get();
					slow_print("\"Dear god...\"", 40);
					cin.get();
					slow_print("You found fear; agility increased!\n", 30);
				}
				else if((i == 3)&&(j == 0)&&(cf == 2)&&(line == "Search Drawer 1"))
				{
					gs++;
					raise_stat(mobs);
					slow_print("The morgue...", 55);
					cin.get();
				}
				else if((i == 3)&&(j == 0)&&(cf == 2)&&(line == "Search Drawer 2"))
				{
					printf("April 15: Mom says we hav to go far away. She says daddy is not himself. She says its not safe but if we\n");
					printf("leave daddy he will be lonely. Daddy tells me he doz not want to be lonely. He says we will be to-get-her\n");
					printf("forevr no matter what. I belive in daddy!");
					cin.get();
					printf("\n");
					slow_print("\"Daddy believes in you too, sweety\"", 40);
					cin.get();
				}
				else if((i == 3)&&(j == 7)&&(cf == 2)&&(line == "Open body drawer"))
				{
					slow_print("You found delusion; strength increased!", 30);
					cin.get();
					slow_print("...", 100);
					cin.get();
					slow_print("\"Janet! There you are! Come on, we have to go find Cindy!\"", 55);
					cin.get();
				}
				else if((i == 4)&&(j == 4)&&(cf == 2)&&(line == "Listen")&&(!sit->second->check))
				{
					slow_print("\"I know, you know.\"", 40);
					cin.get();
					slow_print("\"You know what you did! You know, you know!\"", 40);
					cin.get();
					slow_print("\"I can hear it.\"", 40);
					cin.get();
					slow_print("\"In the way you breathe.\"", 40);
					cin.get();
					slow_print("\"In the way you walk.\"", 40);
					cin.get();
					slow_print("\"I hear it all!\"\n", 40);
				}
				else if((i == 4)&&(j == 7)&&(cf == 2)&&(line == "Open body drawer"))
				{
					gs++;
					raise_stat(mobs);
				}
				else if((i == 5)&&(j == 7)&&(cf == 2)&&(line == "Look at table"))
					slow_print("You found fear; agility increased.\n",30);
				else if((i == 5)&&(j == 7)&&(cf == 2)&&(line == "Look at table!")&&(!sit->second->check))
				{
					slow_print("She's holding a torn diary page.", 30);
					cin.get();
					printf("April 20: Mom tried to leeve with me but daddy stoped her. He says he wants us to be to-get-her forevr.\n");
					printf("Mommy cried and tried to leave but daddy took me away. We went to the park and he held me real tight.\n");
					printf("He told me he wont let her take me. I just want daddy and mom to be happy agin.");
					cin.get();
					printf("\n");
					slow_print("...", 100);
					cin.get();
					slow_print("You pass out.", 30);
					cin.get();
					slow_print("...", 100);
					cin.get();
					slow_print("You wake up in a white bed, it's still night out.\n", 30);
					i = 0; 
					j = 0;
					f2 = f;
					f = f1;
					cf = 1;
				}
				else if((i == 5)&&(j == 0)&&(cf == 1)&&(line == "Search Cabinet"))
				{
					slow_print("You are about to read your file. This action is not reversible, are you sure you wish to continue?(y/n)\n", 30);
					cin >> cd;
					cin.get();
					while((cd != "y")&&(cd != "n"))
					{
						printf("Invalid input.\n");
						cin >> cd;
					}
					if(cd == "y")
					{
						printf("Dr. Graham,\n\n");
						printf("I am sending you a patient named Alan Brown. He is a 34-year-old man with mental issues. On April 21\n");
						printf("Alan killed his 32-year-old wife Janet Brown and his 8-year-old daughter Cindy Brown. Alan had been\n");
						printf("diagnosed with schizophrenia a while back, but it seems after what happened it developed into psychosis.\n");
						printf("His wife was afraid of what he might do so she tried to take the kid and run, Alan did not like this. Alan\n");
						printf("had bad separation anxiety and in a messed-up way, he seemed to think killing them was the only way to\n");
						printf("keep them around. It took a couple of days for my men to find them but when they did, it was just Alan\n");
						printf("and the two bodies hold up in a room. We took him into custody and alerted known relatives of what\n");
						printf("happened. At his court trial they forced Alan to read excerpts from his daughter’s diary to illicit a response\n");
						printf("out of him, but he just kept acting like a doting father. The final ruling was that he was not criminally\n");
						printf("responsible by reason of mental disorder. It honestly makes me sick; the bastard should get the death\n");
						printf("sentence. Anyway, I am sending him your way because I know you do good work at that psychiatric ward.\n");
						printf("Please cure him so he can face judgement.\n\n");
						printf("Thanks in advance,\n");
						printf("Sheriff John Jackson");
						cin.get();
						printf("\n");
						slow_print("\"...Cindy\"", 200);
						cin.get();
						slow_print("\"...Janet\"", 200);
						cin.get();
						slow_print("\"H-how...\"", 100);
						cin.get();
						slow_print("Tears begin to leave your eyes.", 30);
						cin.get();
						slow_print("You take the knife and point it at your face.", 30);
						cin.get();
						slow_print("\"Daddy's so sorry, don't worry, we'll be together forever.\"\n", 100);
						slow_print("You slam your head down on the knife.", 30);
						cin.get();
						slow_print("...", 100);
						cin.get();
						slow_print("The cops find you in a pool of blood in the doctors office.\n", 30);
						slow_print("Everywhere around you are the dead bodies of patients.", 30);
						cin.get();
						slow_print("Next to you is the dead body of Dr. Graham.", 30);
						cin.get();
						slow_print("In your hand is a picture of your family...", 30);
						cin.get();
						slow_print("The photo shows you next to the corpses of your wife and daughter.", 30);
						cin.get();
						printf("Congratulations! Insomnia cured!");
						cin.get();
						printf("You can finally get some rest.\n");
						break;
					}
				}
				//If action is in a stairwell, changes floors
				else if((((i == 0)&&(j == 3))||((i == 5)&&(j == 3)))&&(line == "Descend Stairs")&&(cf == 1))
				{	
					f1 = f;
					f = f2;
					cf = 2;
				}
				else if((((i == 0)&&(j == 3))||((i == 5)&&(j == 3)))&&(line == "Ascend Stairs")&&(cf == 2))
				{
					f2 = f;
					f = f1;
					cf = 1;
				}
				//Mark action as done
				sit->second->check = true;
				printf("\n");
			}
		}
		//Player asks to heal
		else if(line == "h")
		{
			//Checks to make sure player's health isn't full
			if(p->Willpower == 100)
				printf("Willpower(hp) is already full.\n");
			//If not full, heals player
			else
			{
				//Double checks that player wants to heal
				printf("Willpower is %d. Are you sure you want to use courage? (y/n)\n", p->Willpower);
				cin >> cd;
				cin.get();
				while((cd != "y")&&(cd != "n"))
				{
					printf("Invalid input.\n");
					cin >> cd;
				}
				//Heals player
				if(cd == "y")
				{
					//Checks if player has courage
					if(p->Courage == 0)
						printf("\nYou don't have any courage.\n");
					//If player has courage, heals
					else
					{
						printf("\nYou look at a picture of your family. Willpower(hp) replenished!\n");
						p->Willpower = 100;
						p->Courage--;
					}

				}
			}
			printf("\n");
		}
		//Player wishes to see info
		else if(line == "i")
		{
			//If player's health isn't too low tells them they're fine
			if(p->Willpower > 40)
				printf("You have %d willpower(hp), you can still fight on!\n", p->Willpower);
			//If player's health is low, tells them to heal
			else if(p->Willpower <= 40)
				printf("You have %d willpower(hp), you're almost out of motivation, use courage to replenish.\n", p->Willpower);
			//Tells the player their stats along with any weapons they have
			printf("You have level %d strength.\n", p->Strength);
			printf("You have level %d agility.\n", p->Agility);
			printf("You have level %d accuracy.\n", p->Accuracy);
			printf("You have level %d defense.\n\n", p->Defense);
			if(gs < 7)
				printf("Current Objective:\n");
			if(gs == 0)
				printf("Search for clues about your situation.\n\n");
			else if(gs == 1)
				printf("Search for clues in room 204.\n\n");
			else if(gs == 2)
				printf("Search for clues at the reception desk.\n\n");
			else if(gs == 3)
				printf("Investigate the morgue.\n\n");
			else if(gs == 4)
				printf("Search for clues in room 202.\n\n");
			else if(gs == 5)
				printf("Cut your way to the doctor's office.\n\n");
			else if(gs == 6)
				printf("Find your truth in the doctor's office.\n\n");
			printf("Inventory:\n");
			printf("%d Courage\n", p->Courage);
			if(p->BoneSaw)
				printf("Accomplice's Bone Saw: High Strength, Small Agility\n");
			if(p->Scythe)
				printf("Harvester's Scythe: High Accuracy, Medium Strength\n");
			if(p->DOG)
				printf("Delusion Of Grandeur: High Defense, Medium Strength, Small Agility\n");
			if(p->Scalpel)
				printf("Old Spaniard's Scalpel: High Agility, Medium Accuracy, Medium Strength\n");
			if(p->Knife)
				printf("Knife.\n");
			printf("\n");
		}
		//Saves game then outputs wheter or not save failed
		else if(line == "S")
		{
			if(Save(i, j, gs, cf, d, r, f1, f2, p, mobs))
				printf("Game Saved.\n");
			else
				printf("Save Failed.\n");
		}
		//Shows options again
		else if(line == "o")
		{
			printf("Type one of the cardinal directions (lowercase) to move.\n");
			printf("Type 'i'(Info) to view your willpower (health) and your current stats.\n");
			printf("Type ‘a’(Actions) to view current actions you can take.\n");
			printf("Type 'l'(Look) to see the description of your surrounding location.\n");
			printf("Type 'h' (Heal) to use courage and replenish your willpower.\n");
			printf("Type 'S'(Save) to save your game.\n");
			printf("Type 'q'(Quit) to quit the game.\n");
			printf("Type 'o'(Options) to see these options again.\n\n");
		}
		//Outputs room description
		else if(line == "l")
			printf("%s\n\n", f[i][j]->description.c_str());
		//Outputs possible actions in room
		else if(line == "a")
		{
			for(sit = f[i][j]->actions.begin(); sit !=  f[i][j]->actions.end(); sit++)
				printf("%s\n", sit->first.c_str());
			printf("\n");
		}
		//If player wants to move a direction
		else if((line == "n")||(line == "s")||(line == "w")||(line == "e"))
		{
			//Checks to see if move is possible
			nit = f[i][j]->adj.find(line);
			//If not, outputs error statement
			if(nit == f[i][j]->adj.end())
				printf("Cannot go that direction.\n\n");
			//If door is locked, tells player
			else if(!nit->second->lock)
				printf("Door is locked, need a key to access\n\n");
			//Else, moves to space
			else
			{
				i = nit->second->loc.first;
				j = nit->second->loc.second;
				//Outputs room description
				printf("%s\n\n", f[i][j]->description.c_str());
				//Outputs special dialogue associated with that area
				if((i == 1)&&(j == 0)&&(d == 0))
				{
					slow_print("\"I have to find my family.\"\n\n", 40);
					d++;
				}
				else if((i == 1)&&(j == 3)&&(d == 1))
				{
					slow_print("\"It feels like I'm being followed.\"\n\n", 40);
					d++;
				}
				else if((i == 1)&&(j == 0)&&(gs == 2)&&(d == 2))
				{
					slow_print("\"The reception desk should have more clues.\"\n\n",40);
					d++;
				}
				else if((i == 1)&&(j == 7)&&(gs == 0))
				{
					sit = f1[0][7]->actions.find("Search Dresser");
					if(sit->second->check)
					{
						slow_print("You feel someone behind you.", 40);
						cin.get();
						slow_print("You turn aroud to see a man in white approaching you.\n", 40);
						slow_print("He pokes you with something sharp and your vision starts to blur.\n", 40);
						slow_print("Slowly, everything becomes black.", 40);
						cin.get();
						slow_print(". . .", 100);
						cin.get();
						i = 0;
						j = 0;
						slow_print("You wake up in a white bed, it's still night out.", 30);
						cin.get();
						slow_print("You feel like shit.", 30);
						cin.get();
						printf("\n");
						gs++;
						raise_stat(mobs);
					}
				}
				else if((i == 1)&&(j == 1)&&(gs == 1))
				{
					sit = f1[2][1]->actions.find("Try light switch");
					if(sit->second->check)
					{
						slow_print("A man in white was waiting behind the door for you.", 30);
						cin.get();
						slow_print("You push him out the way and run down the hall.", 30);
						cin.get();
						slow_print("It appears you have escaped.", 30);
						cin.get();
						printf("\n");
						i = 1;
						j = 7;
						r++;
					}
				}
				//Generate monster
				else if(spawn(i, j, cf))
				{
					if(game_stage(gs))
					{
						if((i == 3)&&(j == 3)&&(gs == 5))
						{
							slow_print("\"Come on.\"", 55);
							cin.get();
							slow_print("\"Find your truth.\"", 55);
							cin.get();
							mobs[3]->health += 70;
							mobs[3]->accuracy += 5;
							mobs[3]->damage += 20;
						}
						if(combat(p, renemy(mobs, gs)))
						{
							if(gs != 5)
								slow_print("You survived the night terrors this time.\n\n", 30);
							else if(((i == 3)||(i == 4))&&(j == 3)&&(gs == 5))
							{
								slow_print("This one was wearing a nametag.", 30);
								cin.get();
								cin.get();
								slow_print("\"Dr. Graham.\"", 30);
								cin.get();
								gs++;
							}
							else
								slow_print("There's so much blood on your hands...\n\n", 30);
						}
						else
						{
							if(((i == 3)||(i == 4))&&(j == 3)&&(gs == 5))
							{
								mobs[3]->health -= 70;
								mobs[3]->accuracy -= 5;
								mobs[3]->damage -= 20;
							}
							slow_print("Willpower deplenished, you can't go on.", 30);
							cin.get();
							cin.get();
                            if(p->Death == 3)
                            {
                                if(gs != 5)
									slow_print("The night terrors won.", 30);
								else
									slow_print("The man in white won.", 30);
                                cin.get();
								if(gs != 5)
									slow_print("The man in white finds you dead in the hallway.", 30);
								else
									slow_print("They broke you.", 30);
                                cin.get();
                                break;
                            }
							slow_print("You wake up in a white bed, it's still night out.\n\n", 30);
							if(cf == 2)
							{
								cf = 1;
								f2 = f;
								f = f1;
							}
							i = 0;
							j = 0;
							if(p->Death == 0)
								p->Willpower = 50;
							else if(p->Death == 1)
								p->Willpower = 25;
							else if(p->Death == 2)
								p->Willpower = 10;
							p->Death++;
						}
					}
				}
			}
		}
	//Does nothing for improper input
	}

//Deletes all allocated memory to prevent memory leaks
	clean_m(mobs);
	clean(f1);
	clean(f2);
	delete p;

	return 0;
}

/*Function to read in data*/
void read_in(vector<vector<Room *>> &f, ifstream &fin)
{
	string line, cd, action;		//Strings to format data
	int i, j, k, l, c;				//Ints to format read in
	stringstream ss;				//Stringstream to extract data
	Action *a;						//Tmp action struct
	Room *r;						//Tmp room struct

//Resizes graph and reads in data
	f.resize(6);
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 8; j++)
		{
			//Creates a room pointer then reads in all of its data
			getline(fin, line);
			r = new Room;
			ss.clear();
			ss.str(line);
			ss >> r->lock;
			ss >> k;
			for(l = 0; l < k; l++)
			{
				//Reads in possible directions
				ss >> cd;
				r->directions.push_back(cd);
			}
			ss >> k;
			for(l = 0; l < k; l++)
			{
				//Creates a action pointer then reads in all of its data
				a = new Action;
				getline(fin, line);
				ss.clear();
				ss.str(line);
				ss >> a->check >> c >> action >> a->item;
				replace(action.begin(), action.end(), '-', ' ');
				getline(fin, a->description);
				//Checks if action is a key
				if(c != -1)
				{
					a->lock.first = c / 8;
					a->lock.second = c % 8;
				}
				else
				{
					a->lock.first = -1;
					a->lock.second = -1;
				}
				//Adds action keyed on its pointer to the map
				r->actions.insert(make_pair(action, a));			
			}
			getline(fin, r->description);
			r->loc.first = i;
			r->loc.second = j;
			//Pushes room pointer onto the graph
			f[i].push_back(r);
		}
	}
}

/*Function to create adjacency lists*/
void adj_list(vector<vector<Room *>> &f)
{
	size_t i, j, k;			//Variables to keep track of size

//Iterates through each room's vector creating an adjacency list
	for(i = 0; i < f.size(); i++)
	{
		for(j = 0; j < f[i].size(); j++)
		{
			for(k = 0; k < f[i][j]->directions.size(); k++)
			{
				if(f[i][j]->directions[k] == "N")
					f[i][j]->adj.insert(make_pair("n", (f[i-1][j])));
				else if(f[i][j]->directions[k] == "S")
					f[i][j]->adj.insert(make_pair("s", (f[i+1][j])));
				else if(f[i][j]->directions[k] == "W")
					f[i][j]->adj.insert(make_pair("w", (f[i][j-1])));
				else if(f[i][j]->directions[k] == "E")
					f[i][j]->adj.insert(make_pair("e", (f[i][j+1])));
			}
		}
	}
}

/*Function to delete allocated memory*/
void clean(vector<vector<Room *>> &f)
{
	map<string, Action *>::iterator sit;	//Map iterator of actions
	size_t i, j;							//Variables to keep track of size
	
//Iterates through graph and each room's actions deleting all pointers	
	for(i = 0; i < f.size(); i++)
	{
		for(j = 0; j < f[i].size(); j++)
		{
			for(sit = f[i][j]->actions.begin(); sit != f[i][j]->actions.end(); sit++)
				delete sit->second;
			delete f[i][j];
		}
	}
}

/*Function to delete allocated memory*/
void clean_m(vector<Enemy *> &mobs)
{
	size_t i;

	for(i = 0; i < mobs.size(); i++)
		delete mobs[i];
}

/*Function to check if area allows enemy spawn*/
bool spawn(int i, int j, int cf)
{
	//Return true if in hallway, else return false
	if((i == 1)&&(cf == 1))
		return true;
	else if((i == 2)&&(j == 3)&&(cf == 1))
		return true;
	else if((i == 3)&&(j == 3)&&(cf == 1))
		return true;
	else if((i == 4)&&(j >= 3)&&(j <= 7)&&(cf == 1))
		return true;
	else if((i == 1)&&(j >= 1)&&(j <= 5)&&(cf == 2))
		return true;
	else if((i == 2)&&(j >= 1)&&(j <= 5)&&(cf == 2))
		return true;
	else if((i == 3)&&(j >= 3)&&(j <= 6)&&(cf == 2))
		return true;
	else if((i == 4)&&(j >= 3)&&(j <= 6)&&(cf == 2))
		return true;
	return false;	
}

/*Function that roles for a chance to start combat*/
bool game_stage(int gs)
{
	int r;		//Variable for random number

//Seed random number generator then set r equal 
//to a random number between 1 and 10
	srand(time(NULL));
	r = rand() % 10 + 1;

//Depending on the current game stage 
//return true. This controls monster 
//spawn rate
	if(gs == 0)
	{
		if(r < 2)
			return true;
	}
	else if(gs == 1)
	{
		if(r < 3)
			return true;
	}
	else if(gs == 2)
	{
		if(r < 4)
			return true;
	}
	else if(gs == 3)
	{
		if(r < 5)
			return true;
	}
	else if(gs == 4)
	{
		if(r < 6)
			return true;
	}
	else if(gs == 5)
		return true;

	return false;
}

/*Function that returns a random enemy*/
Enemy* renemy(vector<Enemy *> mobs, int gs)
{
	int r;

	srand(time(NULL));
	r = rand() % 3;

	if(gs < 5)
	{
		slow_print(mobs[r]->type, 30);
		printf("\n");
		return mobs[r];
	}
	else
	{
		slow_print(mobs[3]->type, 30);
		printf("\n");
		return mobs[3];
	}
}

/*Function to raise enemy stats*/
void raise_stat(vector<Enemy *> &mobs)
{
	size_t i;

	for(i = 0; i < mobs.size(); i++)
	{
		mobs[i]->health += 10;
		mobs[i]->damage += 5;
		mobs[i]->speed += 1;
		mobs[i]->accuracy += 1;
	}
}
