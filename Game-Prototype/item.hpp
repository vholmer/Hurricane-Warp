#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

struct Item {

private:
	string description;
	string name;

	int damage;

public:
	Item(string description, string name, int damage);

	string getDescription() const;

	string getName() const;

	int getDamage() const;
};

#endif