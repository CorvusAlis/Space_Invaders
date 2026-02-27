#include "GameStateManager.h"

GameStateManager::GameState()
{
	currentState = State::Playing;
}

bool GameStateManager::areEnemiesAlive(const Enemy enemies[][COLS], int rows, int cols) const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (enemies[i][j].isActive())
				return true;
		}
	}
	return false;
}

void GameStateManager::update(const Enemy enemies[][COLS], int rows, int cols)
{
	if (currentState != State::Playing)
		return;
	
	if (!areEnemiesAlive(enemies, rows, cols))
		currentState = State::Win;
}

void GameStateManager::setGameOver()
{
	currentState = State::GameOver;
}

GameStateManager GameStateManager::getState() const
{
	return currentState;
}
