#include<algorithm>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<thread>
#include<chrono>
#include<map>

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

/*Function to save current game state*/
bool Save(int i, int j, int gs, int cf, int d, int r, vector<vector<Room *>> f1, vector<vector<Room *>> f2, Player *p, vector<Enemy *> mobs)
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
		 << p->Agility << " " << p->Accuracy << " " << p->Defense << " " << p->Death << " ";
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
	for(col = 0; col <= 3; col++)
	{
		fout << mobs[col]->type << "\n";
		fout << mobs[col]->health << " " 
			 << mobs[col]->damage << " "
			 << mobs[col]->speed << " "
			 << mobs[col]->accuracy << "\n";
	}
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

void make_enemy(vector<Enemy *> &mobs, ifstream &fin)
{
	int i;
	Enemy *e;
	string line;
	stringstream ss;

	for(i = 0; i <= 3; i++)
	{
		e = new Enemy;
		getline(fin, e->type);
		getline(fin, line);
		ss.clear();
		ss.str(line);
		ss >> e->health >> e->damage >> e->speed >> e->accuracy;
		mobs.push_back(e);
	}
}
