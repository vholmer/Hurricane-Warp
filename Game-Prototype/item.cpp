#include "item.hpp"

Item::Item(string description, string name, int damage) {
	this->description = description;
	this->name = name;
	this->damage = damage;
}

string Item::getDescription() const {
	return this->description;
}

string Item::getName() const {
	return this->name;
}

int Item::getDamage() const {
	return this->damage;
}