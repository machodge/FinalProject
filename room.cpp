#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>


using namespace std;

/*Room data structure to hold all data pertaining to 
rooms*/
struct Room
{
	char type;					//Room type
	string description;			//Room description
	vector<string> items;		//Items in room
	vector<string> actions;		//Allowed actions in room
	vector<Room *> adj;			//Accessable points from room
	int Save(int i, int j);		//Prototype to save game state
};

int main(int argc, char *argv[])
{
	vector<vector<Room *> > game_map;		//Game map
	string line, item, action;				//Stings to read in data
	int i, j, k, v, l;						//Variables to format data read in
	stringstream ss;						//Stringstream for data read in
	ifstream fin;							//File in to read from file
	Room *r;								//Tmp pointer to room struct
	
	fin.open(argv[1]);		//Open file name given on second argument

	//Pull additional info from file and game state here
	
//Pull info to make rooms from file
	while(getline(fin, line))
	{
		ss.clear();
		ss.str(line);
		ss >>  v;
		game_map.resize(v);
		for(i = 0; i < v; i++)
		{
			getline(fin, line);
			for(j = 0; j < v; j++)
			{
				r = new Room;
				ss.clear();
				ss.str(line);
				ss >> r->type >> r->description;
				getline(fin, line);
				ss.clear();
				ss.str(line);
				ss >> k;
				for(l = 0; l < k; i++)
				{
					ss >> item;
					r->items.push_back(item);
				}
				getline(fin, line);
				ss.clear();
				ss.str(line);
				ss >> k;
				for(l = 0; l < k; i++)
				{
					ss >> action;
					r->actions.push_back(action);
				}
				game_map[i].push_back(r);
			}
		}
	}

//Closes file
	fin.close();

//Creates adjacency list
	for(i = 0; i < game_map.size(); i++)
	{
		for(j = 0; j < game_map[i].size(); j++)
		{
			if((i-1) >= 0)
			{
				if((game_map[i-1][j]->type == 'h')||(game_map[i-1][j]->type == 'd')||(game_map[i-1][j]->type == 'o' && game_map[i][j]->type != 'r')||(game_map[i-1][j]->type == 's'))
					game_map[i][j]->adj.push_back(game_map[i-1][j]);
			}
			if((i+1) < game_map[i].size())
			{
				if((game_map[i+1][j]->type == 'h')||(game_map[i+1][j]->type == 'd')||(game_map[i+1][j]->type == 'o' && game_map[i][j]->type != 'r')||(game_map[i+1][j]->type == 's'))
					game_map[i][j]->adj.push_back(game_map[i+1][j]);
			}
			if((j-1) >= 0)
			{
                if((game_map[i][j-1]->type == 'h')||(game_map[i][j-1]->type == 'd')||(game_map[i][j-1]->type == 'o' && game_map[i][j]->type != 'r')||(game_map[i][j-1]->type == 's'))
					game_map[i][j]->adj.push_back(game_map[i][j-1]);
			}
			if((j+1) < game_map[i].size())
			{
                if((game_map[i][j+1]->type == 'h')||(game_map[i][j+1]->type == 'd')||(game_map[i][j+1]->type == 'o' && game_map[i][j]->type != 'r')||(game_map[i][j+1]->type == 's'))
					game_map[i][j]->adj.push_back(game_map[i][j+1]);
			}
		}
	}
	
//Deletes all allocated memory to prevent memory leaks
	for(i = 0; i < game_map.size(); i++)
		for(j = 0; j < game_map[i].size(); j++)
			delete game_map[i][j];
	game_map.clear();

	return 0;
}

/*Function to save current game state*/
int Save(int i, int j)
{
	return 0;
}
