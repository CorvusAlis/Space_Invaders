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

//control de enemigos vivos
bool GameStateManager::areEnemiesAlive(const Enemy enemies[][COLS], int rows, int cols) const
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (enemies[i][j].isActive())
				return true;
	
	return false;
}

//PANTALLAS

//MENU PRINCIPAL
void GameStateManager::showMenu()
{
	system("cls");
	
	std::cout << "====== SPACE INVADERS ======\n\n";
	std::cout << "[ENTER] Jugar\n";
	std::cout << "[I] Instrucciones\n";
	std::cout << "[ESC] Salir\n";
	
	int key = _getch();
	
	if (key == 13)
		currentState = State::Playing;
	
	else if (key == 'i' || key == 'I')
		currentState = State::Instructions;
	
	else if (key == 27)
		currentState = State::Exit;
}

//INSTRUCCIONES
void GameStateManager::showInstructions()
{
	system("cls");
	
	std::cout << "====== INSTRUCCIONES ======\n\n";
	std::cout << "Mover: Flechas\n";
	std::cout << "Disparar: Espacio\n\n";
	std::cout << "Presione ESC para volver al menu\n";
	
	int key = _getch();
	
	if (key == 27)
		currentState = State::Menu;
}

//VICTORIA
void GameStateManager::showWin()
{
	system("cls");
	
	std::cout << "¡VICTORIA!\n\n";
	std::cout << "Presione ENTER para volver al menu principal\n";
	
	int key = _getch();
	
	if (key == 13)
		currentState = State::Menu;
}

//DERROTA
void GameStateManager::showGameOver()
{
	system("cls");
	
	std::cout << "GAME OVER\n\n";
	std::cout << "Presione ENTER para volver al menu\n";
	
	int key = _getch();
	
	if (key == 13)
		currentState = State::Menu;
}
