#pragma once
#include "EngineUtils.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Window.h"
#include "Actor.h"
#include "common.h"
#include "LogRedirect.h"
#include "Collisionfunctions.h"

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() {}
public:

	void initWindow(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height);
	void load();
	bool loop();
	void unload();
	void close();

	void	addActor(Actor* actor);
	void	removeActor(Actor* actor);
	Actor*	searchActor(char* actorName);
	void	addCollision(CollisionComponent* collision);
	void	removeCollision(CollisionComponent* collision);
	std::vector<CollisionComponent*> getAllCollisions();

	entry::InputState m_inputState;

private:
	Window window;

	std::filebuf file;
	CoutRedirect pipe;
	std::vector<Actor*> actors;
	std::vector<CollisionComponent*> collisions;
	std::vector<Actor*> pendingActors;
	std::vector<CollisionComponent*> pendingCollisions;
};

