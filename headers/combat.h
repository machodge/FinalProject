struct Player{

	int health;
	int willpower;

	vector <Item> items;
	vector <Weapon> weapons;
	vector <Attack> attacks;

	void TakeDamage(int amount);


};

struct Enemy{

	int hp;
	vector<Attack> attacks;
	void TakeDamage(int amount);

};

struct Attack{

	string name;
	int damage;

}

struct 
