#include "GameStateManager.h"

GameState::GameState()
{
	currentState = GameState::Playing;
}

bool GameState::areEnemiesAlive(const Enemy enemies[][COLS], int rows, int cols) const
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

void GameState::update(const Enemy enemies[][COLS], int rows, int cols)
{
	if (currentState != GameState::Playing)
		return;
	
	if (!areEnemiesAlive(enemies, rows, cols))
		currentState = GameState::Win;
}

void GameState::setGameOver()
{
	currentState = GameState::GameOver;
}

GameState GameState::getState() const
{
	return currentState;
}
