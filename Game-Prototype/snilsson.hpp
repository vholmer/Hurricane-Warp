#ifndef SNILSSON_HPP
#define SNILSSON_HPP

#include "actor.hpp"

struct Actor;
struct Player;

struct Snilsson : public Actor {
	Snilsson(string name, string description);

	virtual void act(Engine* engine) override;

	virtual void die(Engine* engine) override;

private:
	Player* weakestPlayer();
};

#endif