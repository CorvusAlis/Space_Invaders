//esta clase se encargara de manejar los estados del juego (menu, victoria, derrota) que deben verse en pantalla
//se deja desacoplado del main para no ensuciar el gameloop

#pragma once
#include "Enemy.h"

class GameState
{
private:
	GameState currentState;
	
public:
	GameState();
	
	void update(const Enemy enemies[][COLS], int rows, int cols);
	bool areEnemiesAlive(const Enemy enemies[][COLS], int rows, int cols) const;
	
	void setGameOver();
	GameState getState() const;
};
