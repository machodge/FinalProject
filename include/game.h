#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include<chrono>
#include<map>

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

/*Player data structure to hold all data pertaining to 
 rooms*/
struct Player
{
    //Hp potion
	int Courage;
    //Player stats
	int Willpower;
    int Strength;
    int Agility;
    int Accuracy;
    int Defense ;
    //Game weapons
	bool BoneSaw;
    bool Scythe;
    bool DOG;
    bool Scalpel;
	bool Knife;
};

/*Action data structure to hold all data pertaining to
  actions*/
struct Action
{
    bool check;						//Checks if action has been done
    string item;					//Item related to the action
    string description;				//Description of action
    pair <int, int> lock;			//Cordinate to unlock door if item is a key
};

/*Room data structure to hold all data pertaining to
rooms*/
struct Room
{
    bool lock;                      //Wheter or not room is locked
    string description;             //Room description
    pair <int, int> loc;            //Room location
    map<string, Action *>  actions; //Allowed actions in room
    vector<string> directions;      //Allowed directions
    map<string, Room *> adj;        //Accessable points from room
};

/*Function to save current game state*/
bool Save(int i, int j, int gs, int cf, int d, int r, vector<vector<Room *>> f1, vector<vector<Room *>> f2, Player *p)
{
	size_t k;								//Variable for formatting
	string line;							//String to format data
	ofstream fout;							//Output file
	int row, col, fc;						//Variables for formatting
	vector<vector<Room *>> f;				//Variable for formatting
	map<string, Action *>::iterator nit;	//Action iterator

//Opens save file
	fout.open("data/save.txt");
//If save fails return false
	if(fout.fail())
		return false;
//Formats and outputs all data in save file
	fout << gs << " " << cf << " " << i << " " << j << " " << d << " " << r << "\n";
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
		fout << "1 ";
	else 
		fout << "0 ";
	if(p->Knife)
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
//Closes file
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
