#include <fstream>
#include <iostream>
#include <vector>
#include <inventory.h>
using namespace std;

bool itemInit(vector <Item> &v) {
    fstream fin;
    int numModifiers, statInc;
    string stat;
    string fileName = "data/items.txt";
    fin.open(("data/items.txt"));

    if (fin.fail) return false;

    while (fin >> numModifiers) {
        Item item;
        for (int i = 0; i < numModifiers; i++) {
            fin >> stat;

            switch (stat) {
            case "name": 
                fin >> item.name;
                break;

            case "description":
                fin >> item.description;
                break;

            case "healthInc":
                fin >> item.healthInc;
                break;

            case "willInc":
                fin >> item.willInc;
                break;
                
            case "damageInc":
                fin >> item.damageInc;
                break;

            case "defenceInc":
                fin >> item.defenceInc;
                break;
            
            default:
                return false;
                break;
            }
            
            v.push_back(item);
        }
    }
    return true;
}