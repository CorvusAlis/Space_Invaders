#include <conio2.h>

#include "EnemyGroup.h"

EnemyGroup::EnemyGroup(int startX, int startY, int spacing, int scrWidth)
{
	screenWidth = scrWidth;
	direction = 1;
	speed = 1;
	frameDelay = 10;
	frameCounter = 0;
	
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i] = Enemy(startX + i * spacing, startY, 'W', RED);
	}
}

void EnemyGroup::update()
{
	frameCounter++;
	
	if (frameCounter < frameDelay)
		return;
	
	frameCounter = 0;
	
	bool changeDirection = false;
	
	//deteccion de colision con borde para manjear el "rebote"
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!enemies[i].isActive()) continue;
		
		int nextX = enemies[i].getX() + (direction * speed);
		
		if (nextX <= 1 || nextX >= screenWidth)
		{
			changeDirection = true;
			break;
		}
	}
	
	if (changeDirection)
	{
		direction *= -1;
	}
	
	//movimiento del grupo entero
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!enemies[i].isActive()) continue;
		
		enemies[i].setPosition(
							   enemies[i].getX() + (direction * speed),
							   enemies[i].getY()
							   );
		enemies[i].clear();
		enemies[i].draw();
	}
}

void EnemyGroup::draw()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i].isActive())
			enemies[i].draw();
	}
}
