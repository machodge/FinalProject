#include<algorithm>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<thread>
#include<chrono>
#include<vector>
#include<map>

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void slow_print(const string&, unsigned int);	//Prototype to print type writer style

/*Player data structure to hold all data pertaining to 
  rooms*/
struct Player
{
	int Courage;
	int Willpower;
	int Strength;
	int Agility;
	int Accuracy;
	int Defense ;
	bool BoneSaw;
	bool Scythe;
	bool DOG;
	bool Scalpel;
};
/*Action data structure to hold all data pertaining to
  actions*/
struct Action
{
	bool check;
	string item;
	string description;
	pair <int, int> lock;
};
/*Room data structure to hold all data pertaining to 
rooms*/
struct Room
{
	bool lock;						//Wheter or not room is locked
	string description;				//Room description
	pair <int, int> loc;			//Room location
	map<string, Action *>  actions;	//Allowed actions in room
	vector<string> directions;		//Allowed directions 
	map<string, Room *> adj;		//Accessable points from room
};

bool Save(int i, int j, int gs, int cf, int d, vector<vector<Room *>> f1, vector<vector<Room *>> f2, Player *p);	//Protoype to save game state

int main(int argc, char *argv[])
{
	map<string, Action *>::iterator sit;    //Action iterator
	vector<vector<Room *> > f, f1, f2;		//Game map
	map<string, Room *>::iterator nit;		//Map iterator
	string line, action, cd;				//Strings to read in data
	int d, gs, cf, row, col;				//Variables to keep track of game progress
	int i, j, k, l, c, fc;					//Variables to format data read in
	stringstream ss;						//Stringstream for data read in
	ifstream fin;							//File in to read from file
	Player *p;								//Pointer to the player class
	Action *a;								//Tmp pointer to action struct
	Room *r;								//Tmp pointer to room struct
	
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
		fin.open("save.txt");
		getline(fin, line);
		ss.clear();
		ss.str(line);
		if(line.empty())
		{
			printf("Saved game not found, starting a new game.\n\n");
			cd = "NG";
		}
		else
		{
			ss >> gs >> cf >> row >> col >> d;
			getline(fin, line);
		    ss.clear();
	        ss.str(line);
		    ss >> p->Courage >> p->Willpower >> p->Strength >> p->Agility >> p->Accuracy >> p->Defense
			   >> p->BoneSaw >> p->Scythe >> p->DOG >> p->Scalpel;
		}
	}
    
	if(cd == "NG")
	{
		fin.open("game.txt");
		getline(fin, line);
		ss.clear();
		ss.str(line);
		ss >> gs >> cf >> row >> col >> d;
		getline(fin, line);
		ss.clear();
		ss.str(line);
		ss >> p->Courage >> p->Willpower >> p->Strength >> p->Agility >> p->Accuracy >> p->Defense
		   >> p->BoneSaw >> p->Scythe >> p->DOG >> p->Scalpel;
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

		slow_print("You wake up in a white bed, it's still night out.\n\n", 30);
	}
    
	printf("Type one of the cardinal directions (lowercase) to move.\n");
    printf("Type 'i' (Info) to view your willpower (health) and your current stats.\n");
    printf("Type ‘a’ (Actions) to view current actions you can take.\n");
    printf("Type 'l' (Look) to see the description of your surrounding location.\n");
	printf("Type 'h' (Heal) to use courage and replenish your willpower.\n");
    printf("Type 'S' (Save) to save your game.\n");
    printf("Type 'q' (Quit) to quit the game.\n");
    printf("Type 'o' (Options) to see these options again.\n\n");

//Pull info to make rooms from file
	for(fc = 0; fc <= 1; fc++)
	{
		f.resize(6);
		for(i = 0; i < 6; i++)
		{
			for(j = 0; j < 8; j++)
			{
				getline(fin, line);
				r = new Room;
				ss.clear();
				ss.str(line);
				ss >> r->lock;
				ss >> k;
				for(l = 0; l < k; l++)
				{
					ss >> cd;
					r->directions.push_back(cd);
				}
				ss >> k;
				for(l = 0; l < k; l++)
				{
					a = new Action;
					getline(fin, line);
					ss.clear();
					ss.str(line);
					ss >> a->check >> c >> action >> a->item;
					replace(action.begin(), action.end(), '-', ' ');
					getline(fin, a->description);
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
					r->actions.insert(make_pair(action, a));			
				}
				getline(fin, r->description);
				r->loc.first = i;
				r->loc.second = j;
				f[i].push_back(r);
			}
		}
		if(fc == 0)
			f1 = f;
		else if(fc == 1)
			f2 = f;
		f.clear();
	}

//Closes file
	fin.close();
//Creates adjacency list
	for(fc = 0; fc <= 1; fc++)
	{
		if(fc == 0)
			f = f1;
		else if(fc == 1)
			f = f2;
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
		if(fc == 0)
			f1 = f;
		else if(fc == 1)
			f2 = f;
		f.clear();
	}
	i = row;
	j = col;
	if(cf == 1)
		f = f1;
	else
		f = f2;
	
//Takes input from user and plays game
	cin.get();
	//printf("\n");
	while(1)
	{
		getline(cin, line);
		printf("\n");
		if(line == "q")
			break;
		else if(f[i][j]->actions.find(line) != f[i][j]->actions.end())
		{
			if((i == 1)&&(j == 0)&&(d == 0))
			{
				slow_print("I have to find my family.\n\n", 30);
				d++;
			}
			sit = f[i][j]->actions.find(line);
			if((sit->second->check)&&(sit->second->item != "None"))
				slow_print("Action already explored.\n\n", 30);
			else
			{
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
				slow_print(sit->second->description, 30);
				if((i == 0)&&(j == 0)&&(!sit->second->check)&&(line == "Search Dresser"))
					slow_print("\n\"Find your truth.\"", 30);
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
				sit->second->check = true;
				printf("\n\n");
			}
		}
		else if(line == "h")
		{
			if(p->Willpower == 100)
				printf("Willpower(hp) is already full.\n");
			else
			{
				printf("Willpower is %d. Are you sure you want to use courage? (y/n)", p->Willpower);
				cin >> cd;
				while((cd != "y")&&(cd != "n"))
				{
					printf("Invalid input.\n");
					cin >> cd;
				}
				if(cd == "y")
				{
					if(p->Courage == 0)
						printf("You don't have any courage.\n");
					else
					{
						printf("You look at a picture of your family. Willpower(hp) replenished!\n");
						p->Willpower = 100;
						p->Courage--;
					}

				}
			}
			printf("\n");
		}
		else if(line == "i")
		{
			if(p->Willpower > 30)
				printf("You have %d willpower(hp), you can still fight on!\n", p->Willpower);
			else if(p->Willpower < 30)
				printf("You have %d willpower(hp), you're almost out of motivation, use courage to replenish.\n", p->Willpower);
			printf("You have level %d strength.\n", p->Strength);
			printf("You have level %d agility.\n", p->Agility);
			printf("You have level %d accuracy.\n", p->Accuracy);
			printf("You have level %d defense.\n\n", p->Defense);
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
			printf("\n");
		}
		else if(line == "S")
		{
			if(Save(i, j, gs, cf, d, f1, f2, p))
				printf("Game Saved.\n");
			else
				printf("Save Failed.\n");
		}
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
		else if(line == "l")
			printf("%s\n\n", f[i][j]->description.c_str());

		else if(line == "a")
		{
			for(sit = f[i][j]->actions.begin(); sit !=  f[i][j]->actions.end(); sit++)
				printf("%s\n", sit->first.c_str());
			printf("\n");
		}
		else if((line == "n")||(line == "s")||(line == "w")||(line == "e"))
		{
			nit = f[i][j]->adj.find(line);
			if(nit == f[i][j]->adj.end())
				printf("Cannot go that direction.\n\n");
			else if(!nit->second->lock)
				printf("Door is locked, need a key to access\n\n");
			else
			{
				i = nit->second->loc.first;
				j = nit->second->loc.second;
				printf("%s\n\n", f[i][j]->description.c_str());
			}
		}
		else
			printf("Invalid input.\n\n");
	}

//Deletes all allocated memory to prevent memory leaks
	for(fc = 0; fc <= 1; fc++)
	{
		if(fc == 0)
			f = f1;
		else if(fc == 1)
			f = f2;
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
	f2.clear();
	f1.clear();
	f.clear();
	delete p;

	return 0;
}

/*Function to save current game state*/
bool Save(int i, int j, int gs, int cf, int d, vector<vector<Room *>> f1, vector<vector<Room *>> f2, Player *p)
{
	size_t k;
	string line;
	ofstream fout;
	int row, col, fc;
	vector<vector<Room *>> f;
	map<string, Action *>::iterator nit;

	fout.open("save.txt");
	if(fout.fail())
		return false;
	fout << gs << " " << cf << " " << i << " " << j << " " << d << "\n";
	fout << p->Courage << " " << p->Willpower << " " << p->Strength << " "
		 << p->Agility << " " << p->Accuracy << " " << p->Defense << " ";
	if(p->BoneSaw)
		fout << "1 ";
	else 
		fout << "0 ";
	if(p->Scythe)
		fout << "1 ";
	else 
		fout << "0 ";
	if(p->DOG)
		fout << "1 ";
	else
		fout << "0 ";
	if(p->Scalpel)
		fout << "1\n";
	else 
		fout << "0\n";
	for(fc = 0; fc <= 1; fc++)
	{
		if(fc == 0)
			f = f1;
		else if(fc == 1)
			f = f2;
		for(row = 0; row < 6; row++)
		{
			for(col = 0; col < 8; col++)
			{
				if(f[row][col]->lock)
					fout << "1 ";
				else
					fout << "0 ";
				fout << f[row][col]->directions.size() << " ";
				for(k = 0; k < f[row][col]->directions.size(); k++)
					fout << f[row][col]->directions[k] << " ";
				fout << f[row][col]->actions.size() << "\n";
				
				for(nit = f[row][col]->actions.begin(); nit != f[row][col]->actions.end(); nit++)
				{
					if(nit->second->check)
						fout << "1 ";
					else
						fout << "0 ";
					if(nit->second->lock.first == -1)
						fout << "-1 ";
					else
						fout << (nit->second->lock.first*8)+nit->second->lock.second << " ";
					line = nit->first;
					replace(line.begin(), line.end(), ' ', '-');
					fout << line << " " << nit->second->item << "\n";
					fout << nit->second->description << "\n";
				}
				fout << f[row][col]->description << "\n";
			}
		}
	}

	fout.close();
	return true;
}

/*Function to print out string type writer style*/
void slow_print(const string& message, unsigned int millis_per_char) 
{
	for(const char c: message)
	{
		cout << c << flush;
		sleep_for(milliseconds(millis_per_char));
	}
}
