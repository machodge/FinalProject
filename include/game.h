#include<algorithm>
#include<iostream>
#include<map>
using namespace std;

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
    bool lock;                      //Wheter or not room is locked
    string description;             //Room description
    pair <int, int> loc;            //Room location
    map<string, Action *>  actions; //Allowed actions in room
    vector<string> directions;      //Allowed directions
    map<string, Room *> adj;        //Accessable points from room
};

