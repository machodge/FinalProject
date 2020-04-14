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

void slow_print(const string&, unsigned int);

/*Room data structure to hold all data pertaining to 
rooms*/
struct Room
{
	string description;				//Room description
	pair <int, int> loc;			//Room location
	vector<string> items;			//Items in room
	vector<string> actions;			//Allowed actions in room
	vector<char> directions;		//Allowed directions 
	map<char, Room *> adj;			//Accessable points from room
	int Save(int i, int j);			//Prototype to save game state
};

int main(int argc, char *argv[])
{
	vector<vector<Room *> > f1;				//Game map
	map<char, Room *>::iterator nit;		//Map iterator
	string line, item, action;				//Stings to read in data
	int i, j, k, l;							//Variables to format data read in
	stringstream ss;						//Stringstream for data read in
	ifstream fin;							//File in to read from file
	Room *r;								//Tmp pointer to room struct
	char cd;
	
	fin.open(argv[1]);		//Open file name given on second argument

	//Pull additional info from file and game state here
	
//Pull info to make rooms from file
	f1.resize(6);
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 8; j++)
		{
			getline(fin, line);
			r = new Room;
			ss.clear();
			ss.str(line);
			ss >> k;
			for(l = 0; l < k; l++)
			{
				ss >> cd;
				r->directions.push_back(cd);
			}
			getline(fin, line);
			ss.clear();
			ss.str(line);
			ss >> k;
			for(l = 0; l < k; l++)
			{
				ss >> item;
				r->items.push_back(item);
			}
			getline(fin, line);
			ss.clear();
			ss.str(line);
			ss >> k;
			for(l = 0; l < k; l++)
			{
				ss >> action;
				r->actions.push_back(action);
			}
			getline(fin, line);
			ss.clear();
			ss.str(line);
			r->description = line;
			r->loc.first = i;
			r->loc.second = j;
			f1[i].push_back(r);
		}
	}

//Closes file
	fin.close();
//Creates adjacency list
	for(i = 0; i < f1.size(); i++)
	{
		for(j = 0; j < f1[i].size(); j++)
		{
			for(k = 0; k < f1[i][j]->directions.size(); k++)
			{
				if(f1[i][j]->directions[k] == 'N')
					f1[i][j]->adj.insert(make_pair('n', (f1[i-1][j])));
				else if(f1[i][j]->directions[k] == 'S')
					f1[i][j]->adj.insert(make_pair('s', (f1[i+1][j])));
				else if(f1[i][j]->directions[k] == 'W')
					f1[i][j]->adj.insert(make_pair('w', (f1[i][j-1])));
				else if(f1[i][j]->directions[k] == 'E')
					f1[i][j]->adj.insert(make_pair('e', (f1[i][j+1])));
			}
		}
	}
	
	printf("Welcome to Insomnia.\n");
	slow_print("You wake up in a white bed, it's still night out.\n\n", 30);
    printf("Type one of the cardinal directions (lowercase) to move.\n");
	printf("Type 'i' (Info) to view your willpower (health) and your current stats.\n");
	printf("Type ‘h’ (Help) to view current actions you can take.\n");
	printf("Type 'l' (Look) to see the description of your surrounding location.\n");
	printf("Type 's' (Save) to save your game.\n");
	printf("Type 'q' (Quit) to quit the game.\n");
	printf("Type 'o' (Options) to see these options again\n\n");

	i = 0;
	j = 0;
	while(1)
	{
		cin >> cd;
		printf("\n");
		if(cd == 'q')
			break;
		else if(cd == 'o')
		{
			printf("Type one of the cardinal directions (lowercase) to move.\n");
			printf("Type 'i'(Info) to view your willpower (health) and your current stats.\n");
			printf("Type ‘h’(Help) to view current actions you can take.\n");
			printf("Type 'l'(Look) to see the description of your surrounding location.\n");
			printf("Type 's'(Save) to save your game.\n");
			printf("Type 'q'(Quit) to quit the game.\n");
			printf("Type 'o'(Options) to see these options again\n\n");
		}
		else if(cd == 'l')
			printf("%s\n\n", f1[i][j]->description.c_str());

		else if(cd == 'h')
		{
			for(k = 0; k < f1[i][j]->actions.size(); k++)
				printf("%s\n", f1[i][j]->actions[k].c_str());
			printf("\n");
		}
		else if((cd == 'n')||(cd == 's')||(cd == 'w')||(cd == 'e'))
		{
			nit = f1[i][j]->adj.find(cd);
			if(nit == f1[i][j]->adj.end())
				printf("Cannot go that direction.\n\n");
			else
			{
				i = nit->second->loc.first;
				j = nit->second->loc.second;
			}
		}
		else
			printf("Invalid input.\n\n");
	}
//Deletes all allocated memory to prevent memory leaks
	for(i = 0; i < f1.size(); i++)
		for(j = 0; j < f1[i].size(); j++)
			delete f1[i][j];
	f1.clear();

	return 0;
}

/*Function to save current game state*/
int Save(int i, int j)
{
	return 0;
}

void slow_print(const string& message, unsigned int millis_per_char) 
{
	for(const char c: message)
	{
		cout << c << flush;
		sleep_for(milliseconds(millis_per_char));
	}
}
