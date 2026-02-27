#include "GameStateManager.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
//tomo la idea del ultimo proyecto de MAVI con el switch para controlar que estado esta activo
//de esta forma no necesito clases para cada pantalla que se encarguen de renderizar
//esta todo en esta clase, y se llama a distintos metodos desde el main segun que este ocurriendo

GameStateManager::GameStateManager()
{
	currentState = States::Menu;
	running = true;
}

bool GameStateManager::isRunning() const
{
	return running;
}

States GameStateManager::getState() const
{
	return currentState;
}

//CONTROLADOR DE LOS ESTADOS DEL JUEGO
void GameStateManager::run(EnemyGroup& enemyGroup)
{
	switch (currentState)
	{
	case States::Menu:
		showMenu();
	break;
	
	case States::Instructions:
		showInstructions();
	break;
	
	case States::Playing:	//con este controlo si, mientras el juego esta activo, todavia quedan enemigos
		if (!(enemyGroup.areEnemiesAlive()))
			currentState = States::Win;	//si no quedan enemigos activos, mostrar pantalla de victoria (pasa al case de Win)
	break;
	
	case States::Win:
		showWin();
	break;
	
	case States::GameOver:
		showGameOver();
	break;
	
	case States::Exit:
		running = false;
	break;
	}
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
		currentState = States::Playing;
	
	else if (key == 'i' || key == 'I')
		currentState = States::Instructions;
	
	else if (key == 27)
		currentState = States::Exit;
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
		currentState = States::Menu;
}

//VICTORIA
void GameStateManager::showWin()
{
	system("cls");
	
	std::cout << "¡VICTORIA!\n\n";
	std::cout << "Presione ENTER para volver al menu principal\n";
	
	int key = _getch();
	
	if (key == 13)
		currentState = States::Menu;
}

//DERROTA
void GameStateManager::showGameOver()
{
	system("cls");
	
	std::cout << "GAME OVER\n\n";
	std::cout << "Presione ENTER para volver al menu\n";
	
	int key = _getch();
	
	if (key == 13)
		currentState = States::Menu;
}
