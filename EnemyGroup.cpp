#include <conio2.h>

#include "EnemyGroup.h"

#include <conio2.h>
#include "EnemyGroup.h"

EnemyGroup::EnemyGroup(int startX, int startY, int spacing, int scrWidth)
{
	screenWidth = scrWidth;
	
	direction = 1;
	speed = 1;
	
	frameDelay = 10;
	frameCounter = 0;
	
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
				color = GREEN;
			}
			else if (row == 1)
			{
				sprite = 'W';
				color = RED;
			}
			else if (row == 2)
			{
				sprite = 'A';
				color = YELLOW;
			}
			else
			{
				sprite = 'V';
				color = CYAN;
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
	
	//deteccion de colision con los bordes
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
	
	//cambio de direccion y bajar linea
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
				enemies[row][col].clear();
				enemies[row][col].draw();
			}
		}
		
		return; //impide que se mueva horizontalmente en este frmae
	}
	
	//movimiento horizontal de la matriz
	for (int row = 0; row < ENEMY_ROWS; row++)
	{
		for (int col = 0; col < ENEMY_COLS; col++)
		{
			if (!enemies[row][col].isActive()) continue;
			
			enemies[row][col].setPosition(
										  enemies[row][col].getX() + (direction * speed),
											  enemies[row][col].getY()
												  );
			enemies[row][col].clear();
			enemies[row][col].draw();
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
