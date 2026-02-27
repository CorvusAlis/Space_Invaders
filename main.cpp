#include <conio2.h>
#include <windows.h>  //para Sleep() - control de frames - configuracion de consola
#include <iostream>

#include "Player.h"
#include "EnemyGroup.h"
#include "Bullet.h"

int main()
{
	int screenWidth = 60;
	int screenHeight = 30;
	
	const int MAX_BULLETS = 50;
	Bullet bullets[MAX_BULLETS];
	int bulletCount = 0;
	
	const int MAX_ENEMY_BULLETS = 30;
	Bullet enemyBullets[MAX_ENEMY_BULLETS];
	
	//controlan la cantidad de enemigos que deben ser eliminados antes de subir la velocidad - menor numero, mayor dificultad
	int enemiesKilled = 0;
	int difficultyStep = 1;
	
	textbackground(BLACK);
	clrscr();  //solo para inicializar pantalla al inicio
	
	Player player(screenWidth / 2, screenHeight - 2, screenWidth);	//posicionamiento del jugador en la mitad de la pantalla al iniciar el juego
	EnemyGroup enemyGroup(10, 3, 3, screenWidth);
	
	player.draw();
	
	while (true)
	{
		//RECORDAR PASOS FUNDAMENTALES
		//clear() para limpiar el frame anterior - input (en este caso solo para el jugador) - update() para actualizar estados - colisiones - draw() para dibujar nuevo frame
		//esto es para todos los objetos - AUNQUE ESTE CREADO EL OBJETO, NO SE RENDERIZA SOLO!!!!
		
		//CLEAR
		player.clear();
		enemyGroup.clear();
		
		for (int i = 0; i < MAX_BULLETS; i++)	//balas jugador
		{
			if (bullets[i].isActive())
				bullets[i].clear();
		}
		
		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)	//balas enemigo
		{
			if (enemyBullets[i].isActive())
				enemyBullets[i].clear();
		}
		
		//INPUT
		if (kbhit())
		{
			char key = getch();
			player.handleInput(key, bullets, bulletCount, MAX_BULLETS);
		}
		
		//UPDATE
		player.update();
		enemyGroup.update();
		enemyGroup.tryShoot(enemyBullets, MAX_ENEMY_BULLETS);	//probabilidad de disparo de un enemigo de la ultima fila y una columna aleatoria
		
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			bullets[i].update();
		}
		
		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
		{
			enemyBullets[i].update();
		}
		
		//COLISIONES
		//bala-enemigo
		for (int i = 0; i < MAX_BULLETS; i++)
			enemyGroup.checkBulletCollision(bullets[i]);
		
		//bala-jugador
		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
		{
			if (enemyBullets[i].isActive() && player.checkCollision(enemyBullets[i]))
			{
				enemyBullets[i].deactivate();
				player.loseLife();
			}
		}
		
		//incremento de velocidad cada 5 enemigos eleminados
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (enemyGroup.checkBulletCollision(bullets[i]))
			{
				enemiesKilled++;
				
				if (enemiesKilled % difficultyStep == 0)
				{
					enemyGroup.increaseSpeed();
				}
			}
		}
		
		//DRAW
		player.draw();
		enemyGroup.draw();
		
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bullets[i].isActive())
				bullets[i].draw();
		}
		
		for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
		{
			
			if (enemyBullets[i].isActive()){
				enemyBullets[i].draw();
				//std::cout << "PIUM";
			}
		
		}
		
		Sleep(16);  //60 FPS aproximado
	}
	
	return 0;
}
