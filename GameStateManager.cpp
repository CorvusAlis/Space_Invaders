#include "GameStateManager.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
//tomo la idea del ultimo proyecto de MAVI con el switch para controlar que estado esta activo
//de esta forma no necesito clases para cada pantalla que se encarguen de renderizar
//esta todo en esta clase, y se llama a distintos metodos desde el main segun que este ocurriendo

GameStateManager::GameStateManager()
{
	currentState = State::Menu;
	running = true;
}

bool GameStateManager::isRunning() const
{
	return running;
}

//CONTROLADOR DE LOS ESTADOS DEL JUEGO
void GameStateManager::run(const Enemy enemies[][COLS], int rows, int cols)
{
	switch (currentState)
	{
	case State::Menu:
		showMenu();
	break;
	
	case State::Instructions:
		showInstructions();
	break;
	
	case State::Playing:	//con este controlo si, mientras el juego esta activo, todavia quedan enemigos
		if (!areEnemiesAlive(enemies, rows, cols))
			currentState = State::Win;	//si no quedan enemigos activos, mostrar pantalla de victoria (pasa al case de Win)
	break;
	
	case State::Win:
		showWin();
	break;
	
	case State::GameOver:
		showGameOver();
	break;
	
	case State::Exit:
		running = false;
	break;
	}
}

//PANTALLAS

//MENU PRINCIPAL


