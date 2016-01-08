#ifndef DAEMON_HPP
#define DAEMON_HPP

#include "actor.hpp"

struct Actor;
struct Player;

struct Daemon : public Actor {
	Daemon(string name, string description);

	virtual void act(Engine* engine) override;
};

#endif