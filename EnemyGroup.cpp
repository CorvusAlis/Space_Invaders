#include <conio2.h>
#include <cstdlib>
#include <iostream>

#include "EnemyGroup.h"
#include "Bullet.h"


EnemyGroup::EnemyGroup(int sX, int sY, int sp, int scrWidth)
{
	startX = sX;
	startY = sY;
	spacing = sp;
	screenWidth = scrWidth;
	
	direction = 1;
	speed = 1;
	
	frameDelay = 10;
	frameCounter = 0;
	
	initialSpeed = speed;
	
	initializeEnemies(); //la creacion de enemigos se pasa a este metodo
}

void EnemyGroup::initializeEnemies()
{
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			int posX = startX + col * spacing;
			int posY = startY + row * 2;
			
			char sprite;
			int color;
			int score;
			
			if (row == 0)
			{
				sprite = 'X';
				color = MAGENTA;
				score = 40;
			}
			else if (row == 1)
			{
				sprite = 'M';
				color = RED;
				score = 30;
			}
			else if (row == 2)
			{
				sprite = 'W';
				color = CYAN;
				score = 20;
			}
			else
			{
				sprite = 'V';
				color = YELLOW;
				score = 10;
			}
			
			enemies[row][col] = Enemy(posX, posY, sprite, color, score);
		}
	}
}

void EnemyGroup::update()
{
	frameCounter++;
	
	if (frameCounter < frameDelay)
		return;
	
	frameCounter = 0;
	
	bool changeDirection = false;
	
	// detectar colisión con bordes
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (!enemies[row][col].isActive()) continue;
			
			int nextX = enemies[row][col].getX() + (direction * speed);
			
			if (nextX <= 1 || nextX >= screenWidth - 1)
			{
				changeDirection = true;
				break;
			}
		}
		if (changeDirection) break;
	}
	
	if (changeDirection)
	{
		direction *= -1;
		
		for (int row = 0; row < ENEMY_ROWS; row++)
		{
			for (int col = 0; col < ENEMY_COLS; col++)
			{
				if (!enemies[row][col].isActive()) continue;
				
				enemies[row][col].setPosition(
											  enemies[row][col].getX(),
												  enemies[row][col].getY() + 1
													  );
			}
		}
		
		return;
	}
	
	// movimiento horizontal
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (!enemies[row][col].isActive()) continue;
			
			enemies[row][col].setPosition(
										  enemies[row][col].getX() + (direction * speed),
											  enemies[row][col].getY()
												  );
		}
	}
}


void EnemyGroup::draw()
{
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (enemies[row][col].isActive())
				enemies[row][col].draw();
		}
	}
}

void EnemyGroup::clear()
{
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (enemies[row][col].isActive())
				enemies[row][col].clear();
		}
	}
}


//colision bala-enemigo, desactivacion y borrado de ambos

int EnemyGroup::checkBulletCollision(Bullet& bullet)
{
	if (!bullet.isActive())
		return false;
	
	int bulletX = bullet.getX();
	int bulletY = bullet.getY();
	
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (!enemies[row][col].isActive())
				continue;
			
			if (enemies[row][col].getX() == bulletX &&
				enemies[row][col].getY() == bulletY)
			{
				int score = enemies[row][col].getScoreValue();
				enemies[row][col].deactivate();
				bullet.deactivate();
				return score;
			}
		}
	}
	
	return 0;
}

void EnemyGroup::tryShoot(Bullet enemyBullets[], int maxBullets)
{
	//std::cout << "disparo: OK";
	if (rand() % 30 != 0){		//probabilidad de disparo por frame, menor número, más disparos
		//std::cout << "PIUM";
		return; 
	}
	
	//elegir columna aleatoria
	int col = rand() % ENEMY_COLS;
	
	for (int row = ENEMY_ROWS - 1; row >= 0; row--) //buscar enemigo activo más bajo en esa columna
	{
		if (enemies[row][col].isActive())
		{
			
			for (int i = 0; i < maxBullets; i++) //buscar bala libre
			{
				if (!enemyBullets[i].isActive())
				{
					enemyBullets[i] = Bullet(
											 enemies[row][col].getX(),
												 enemies[row][col].getY() + 1,
													 '|',
													 LIGHTRED,
													 1,	//speed
													 1 //direction hacia abajo
													 );
					return;
				}
			}
		}
	}
}

void EnemyGroup::increaseSpeed()
{
	if (frameDelay > 2)   //límite para no romper el juego
		frameDelay -= 1;
}

//control de enemigos vivos
bool EnemyGroup::areEnemiesAlive() const
{
	for (int i = 0; i < ENEMY_ROWS; i++)
		for (int j = 0; j < ENEMY_COLS; j++)
			if (enemies[i][j].isActive())
				return true;
	
	return false;
}

bool EnemyGroup::hasReachedPlayerLine(int playerY)
{
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (enemies[row][col].isActive())
			{
				if (enemies[row][col].getY() >= playerY)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void EnemyGroup::reset()
{
	speed = initialSpeed;
	direction = 1;
	frameDelay = 10;
	frameCounter = 0;

	initializeEnemies();
}
