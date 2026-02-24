#include <conio2.h>

#include "Enemy.h"

Enemy::Enemy()
	: Entity(0, 0, 'W', RED)
{
	active = false;
}

Enemy::Enemy(int startX, int startY, char s, int c)
	: Entity(startX, startY, s, c)
{
	active = true;
}
