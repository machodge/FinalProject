#include<algorithm>
#include<iostream>
#include<string>
#include<thread>
#include<chrono>
#include<map>
using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void slow_print(const string&, unsigned int);   //Prototype to print type writer style

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
    bool lock;                      //Wheter or not room is locked
    string description;             //Room description
    pair <int, int> loc;            //Room location
    map<string, Action *>  actions; //Allowed actions in room
    vector<string> directions;      //Allowed directions
    map<string, Room *> adj;        //Accessable points from room
};

/*Function to print out string type writer style*/
void slow_print(const string& message, unsigned int millis_per_char)
{
    for(const char c: message)
    {
        cout << c << flush;
        sleep_for(milliseconds(millis_per_char));
    }
}
