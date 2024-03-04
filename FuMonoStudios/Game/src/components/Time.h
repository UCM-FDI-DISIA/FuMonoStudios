#pragma once
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Game.h"
class Time
{
public:
	static float getDeltaTime() { return deltaTime; }
private:
	friend class Game;
	static float deltaTime;
};

