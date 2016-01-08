#ifndef CULTIST_HPP
#define CULTIST_HPP

#include "actor.hpp"

struct Actor;
struct Player;

struct Cultist : public Actor {
	Cultist(string name, string description);

	virtual void act(Engine* engine) override;
};

#endif