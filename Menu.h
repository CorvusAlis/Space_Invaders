#pragma once
#include "GameStateManager.h"

class Menu
{
public:
	void show() const;
	GameStateManager handleInput() const;
};
