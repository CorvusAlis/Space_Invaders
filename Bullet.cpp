#include "Bullet.h"
#include <conio2.h>

//constructor por defecto, para la inicializacion del array de balas en el main
Bullet::Bullet()
	: Entity(0, 0, '|', WHITE)
{
	direction = -1;
	speed = 1;
	active = false; //se crea la bala inactiva
}

Bullet::Bullet(int startX, int startY, int dir)
	: Entity(startX, startY, '|', WHITE)
{
	direction = dir;
	speed = 1;
	active = true;
}

void Bullet::update()
{
	if (!active) return;
	
	int newY = y + (direction * speed);
	
	//si sale de pantalla, desactivar - marcar espacio en el array como libre
	//no se maneja memoria ni vectores
	if (newY < 1 || newY > 30)
	{
		//en vez de usar clear() con la posicion previa, se borra el ultimo frame con la posicion actual de la bala
		gotoxy(x, y);
		putch(' ');
		
		deactivate();
		return;
	}
	
	setPosition(x, newY);
	clear();
	draw();
}

void Bullet::setDirection(int dir)
{
	direction = dir;
}
