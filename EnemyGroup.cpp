#include <conio2.h>
#include <cstdlib>

#include "EnemyGroup.h"
#include "Bullet.h"


EnemyGroup::EnemyGroup(int startX, int startY, int spacing, int scrWidth)
{
	screenWidth = scrWidth;
	
	direction = 1;
	speed = 1;
	
	frameDelay = 10;
	frameCounter = 0;

	shotDelay = 45;
	shotCounter = 0;
	
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			int posX = startX + col * spacing;
			int posY = startY + row * 2;
			
			char sprite;
			int color;
			
			if (row == 0)
			{
				sprite = 'M';
				color = MAGENTA;
			}
			else if (row == 1)
			{
				sprite = 'W';
				color = RED;
			}
			else if (row == 2)
			{
				sprite = 'A';
				color = CYAN;
			}
			else
			{
				sprite = 'V';
				color = YELLOW;
			}
			
			enemies[row][col] = Enemy(posX, posY, sprite, color);
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


void EnemyGroup::tryShoot(Bullet bullets[], int maxBullets)
{
	shotCounter++;
	if (shotCounter < shotDelay)
		return;

	shotCounter = 0;

	int activeColumns[ENEMY_COLS];
	int activeCount = 0;

	for (int col = 0; col < ENEMY_COLS; col++)
	{
		for (int row = ENEMY_ROWS - 1; row >= 0; row--)
		{
			if (enemies[row][col].isActive())
			{
				activeColumns[activeCount++] = col;
				break;
			}
		}
	}

	if (activeCount == 0)
		return;

	int selectedCol = activeColumns[rand() % activeCount];

	int shooterRow = -1;
	for (int row = ENEMY_ROWS - 1; row >= 0; row--)
	{
		if (enemies[row][selectedCol].isActive())
		{
			shooterRow = row;
			break;
		}
	}

	if (shooterRow == -1)
		return;

	int shotX = enemies[shooterRow][selectedCol].getX();
	int shotY = enemies[shooterRow][selectedCol].getY() + 1;

	for (int i = 0; i < maxBullets; i++)
	{
		if (!bullets[i].isActive())
		{
			bullets[i] = Bullet(shotX, shotY, 1);
			return;
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

bool EnemyGroup::checkBulletCollision(Bullet& bullet)
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
				enemies[row][col].deactivate();
				bullet.deactivate();
				return true;
			}
		}
	}
	
	return false;
}
