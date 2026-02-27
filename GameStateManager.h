//esta clase se encargara de manejar los estados del juego (menu, victoria, derrota) que deben verse en pantalla
//se deja desacoplado del main para no ensuciar el gameloop

#pragma once
#include "States.h"
#include "EnemyGroup.h"

class GameStateManager
{
private:
	States currentState;
	bool running;
	
	//controla que esta esta corriendo y que mostrar/hacer
	void showMenu();
	void showInstructions();
	void showWin();
	void showGameOver();
	
public:
	GameStateManager();
	States getState() const;
	
	void run(EnemyGroup& enemyGroup);
	void setGameOver();
	
	bool isRunning() const;
};
