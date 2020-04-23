#include<algorithm>
#include<iostream>
#include<map>

using namespace std;

//bool combat(Player *player, Enemy *enemy);

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
    int Defense;
	int Death;
    //Game weapons
	bool BoneSaw;
    bool Scythe;
    bool DOG;
    bool Scalpel;
	bool Knife;
};

/*Enemy data structure to hold all data pertaining to
  enemies*/
struct Enemy 
{
    string type;
	int health;
    int damage;
    int speed;
    int accuracy;
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

bool combat(Player *player, Enemy *enemy);
