#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

struct Item {
	string description;
	string name;

	Item(string description, string name);
};

#endif