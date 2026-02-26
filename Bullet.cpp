#include "Bullet.h"
#include <conio2.h>
#include <iostream>

//constructor por defecto, para la inicializacion del array de balas en el main
Bullet::Bullet()
	: Entity(0, 0, '|', WHITE)
{
	direction = -1;
	speed = 1;
	active = false;
	moveDelay = 2;
	moveTimer = 0;
}

Bullet::Bullet(int startX, int startY, int dir)
	: Entity(startX, startY, '|', WHITE)
{
	direction = dir;
	speed = 1;
	active = true;
	moveDelay = 2;
	moveTimer = 0;
}

Bullet::Bullet(int startX, int startY, char sprite, int color, int spd, int dir)
	: Entity(startX, startY, sprite, color)
{
	direction = dir;
	speed = spd;
	active = true;
	moveDelay = 2;
	moveTimer = 0;
}

void Bullet::update()
{
	if (!active) return;
	
	moveTimer++;
	
	if (moveTimer < moveDelay) return;
	
	int newY = y + (direction * speed);
	//int newY = y + direction;
	
	//si sale de pantalla, desactivar - marcar espacio en el array como libre
	//no se maneja memoria ni vectores
	if (newY < 1 || newY >= 30)
	{		
		deactivate();
		return;
	}
	
	setPosition(x, newY);
	//std::cout << "update bala en Y = " << y << "\n";
	//std::cout << "speed real: " << speed << "\n";
}

void Bullet::setDirection(int dir)
{
	direction = dir;
}

int Bullet::getX() const{
	return x;
}

int Bullet::getY() const{
	return y;
}
