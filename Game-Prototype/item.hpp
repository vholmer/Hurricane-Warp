#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

struct Item {
	int itemID;
	string description;
	string name;

	Item(int id, string description, string name);
};

#endif