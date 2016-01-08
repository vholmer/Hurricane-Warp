#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

struct Item {
	string description;
	string name;

	int damage;

	Item(string description, string name, int damage);
};

#endif