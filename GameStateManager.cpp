#include "GameStateManager.h"
#include <iostream>
#include <conio2.h>
#include <cstdlib>
#include <windows.h>
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
void GameStateManager::run(EnemyGroup& enemyGroup, Player& player)
{
	switch (currentState)
	{
	case States::Menu:
		showMenu();
	break;
	
	case States::Instructions:
		showInstructions();
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
	
	default:
		break;
	}
}

//PANTALLAS

//como no se renderiza entero cada frame, si no que se borra el sprite/caracter anterior y se pone uno nuevo en el siguiente lugar
//antes de cada cambio de estado se tiene que limpiar la pantalla para que no quede nada de la pantalla anterior

//MENU PRINCIPAL
void GameStateManager::showMenu()
{

	std::cout << "====== SPACE INVADERS ======\n\n";
	std::cout << "[ENTER] Jugar\n";
	std::cout << "[I] Instrucciones\n";
	std::cout << "[ESC] Salir\n";
	
	int key = _getch();
	
	if (key == 13){	//enter
		clrscr();
		currentState = States::Playing;
	}
	
	else if (key == 'i' || key == 'I'){
		clrscr();
		currentState = States::Instructions;
	}
	
	else if (key == 27){	//escape
		clrscr();
		currentState = States::Exit;
	}
}

//INSTRUCCIONES
void GameStateManager::showInstructions()
{	
	std::cout << "====== INSTRUCCIONES ======\n\n";
	std::cout << "Mover: [A] y [D]\n";
	std::cout << "Disparar: Espacio\n\n";
	std::cout << "Presione ESC para volver al menu\n";
	
	int key = _getch();
	
	if (key == 27){
		clrscr();
		currentState = States::Menu;
	}
}

//VICTORIA
void GameStateManager::showWin()
{	
	clrscr();
	
	std::cout << "¡VICTORIA!\n\n";
	std::cout << "Presione ENTER para volver al menu principal\n";
	
	int key = _getch();
	
	if (key == 13){
		clrscr();
		currentState = States::Menu;
	}
}

//DERROTA
void GameStateManager::showGameOver()
{
	clrscr();
	
	std::cout << "GAME OVER\n\n";
	std::cout << "Presione ENTER para volver al menu\n";
	
	int key = _getch();
	
	if (key == 13){
		clrscr();
		currentState = States::Menu;
	}
}

void GameStateManager::setState(States newState)
{
	currentState = newState;
}

void GameStateManager::forceWin()
{
	currentState = States::Win;
}

void GameStateManager::forceGameOver()
{
	currentState = States::GameOver;
}
