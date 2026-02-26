#include <conio2.h>
#include <windows.h>  //para Sleep() - control de frames - configuracion de consola

#include "Player.h"
#include "EnemyGroup.h"
#include "Bullet.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
	int screenWidth = 60;
	int screenHeight = 30;
	
	const int MAX_BULLETS = 50;
	const int MAX_ENEMY_BULLETS = 30;

	Bullet bullets[MAX_BULLETS];
	Bullet enemyBullets[MAX_ENEMY_BULLETS];
	int bulletCount = 0;
	
	textbackground(BLACK);
	clrscr();  //solo para inicializar pantalla al inicio
	srand((unsigned int)time(NULL));
	
	Player player(screenWidth / 2, screenHeight - 2, screenWidth);	//posicionamiento del jugador en la mitad de la pantalla al iniciar el juego
	EnemyGroup enemyGroup(10, 3, 3, screenWidth);
	
	player.draw();
	
	while (true)
	{
		//pipeline del frame:
		//1) input, 2) update, 3) colisiones, 4) clear del frame anterior, 5) draw.
		//esto reduce parpadeo porque no se borra el frame al inicio de cada iteracion.

		//INPUT
		if (kbhit())
		{
			char key = getch();
			player.handleInput(key, bullets, bulletCount, MAX_BULLETS);
		}

		//UPDATE
		player.update();
		enemyGroup.update();
		enemyGroup.tryShoot(enemyBullets, MAX_ENEMY_BULLETS);

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			bullets[i].update();
		}

		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
		{
			enemyBullets[i].update();
		}

		//COLISIONES
		for (int i = 0; i < MAX_BULLETS; i++)
			enemyGroup.checkBulletCollision(bullets[i]);

		//CLEAR (frame anterior)
		player.clear();
		enemyGroup.clear();

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			bullets[i].clear();
		}

		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
		{
			enemyBullets[i].clear();
		}

		//DRAW (frame actual)
		player.draw();
		enemyGroup.draw();

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bullets[i].isActive())
				bullets[i].draw();
		}

		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
		{
			if (enemyBullets[i].isActive())
				enemyBullets[i].draw();
		}

		Sleep(16);  //60 FPS aproximado
	}

	
	return 0;
}
