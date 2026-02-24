#include <conio2.h>
#include <windows.h>  //para Sleep() - control de frames

#include "Player.h"
#include "EnemyGroup.h"
#include "Bullet.h"

int main()
{
	int screenWidth = 80;
	int screenHeight = 25;
	
	const int MAX_BULLETS = 50;
	Bullet bullets[MAX_BULLETS];
	int bulletCount = 0;
	
	textbackground(BLACK);
	clrscr();  //solo para inicializar pantalla al inicio
	
	Player player(screenWidth / 2, screenHeight - 2, screenWidth);	//posicionamiento del jugador en la mitad de la pantalla al iniciar el juego
	EnemyGroup enemyGroup(10, 3, 3, screenWidth);
	
	player.draw();
	
	while (true)
	{
		//RECORDAR 3 PASOS FUNDAMENTALES
		//clear() para limpiar el frame anterior - update() para actualizar estados - draw() para dibujar nuevo frame
		//esto es para todos los objetos - AUNQUE ESTE CREADO EL OBJETO, NO SE RENDERIZA SOLO!!!!
		
		//player
		player.clear();
		if (kbhit())
		{
			char key = getch();
			player.handleInput(key, bullets, bulletCount, MAX_BULLETS);
		}
		player.update();
		player.draw();
		
		//enemigos
		enemyGroup.update();
		
		//balas
		//ACTUALIZAR EL ARREGLO PARA RENDERIZAR CADA BALA - MISMA LOGICA QUE PLAYER
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bullets[i].isActive())
			{
				bullets[i].update();
			}
		}		
		
		Sleep(16);  //60 FPS aproximado
	}
	
	return 0;
}
