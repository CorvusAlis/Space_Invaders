#include "Entity.h"
#include <conio2.h>

//constructor
Entity::Entity(int startX, int startY, char s, int c)
{
	x = startX;
	y = startY;
	prevX = x;
	prevY = y;
	sprite = s;
	color = c;
	active = true;
}

//destructor
Entity::~Entity()
{
}

void Entity::draw() const
{
	if (!active) return;
	
	textcolor(color);
	gotoxy(x, y);
	putch(sprite);
}

void Entity::clear() const
{
	//toma la posicion previa del caracter y la "borra" colocando un espacio
	gotoxy(prevX, prevY);
	putch(' ');
}

void Entity::setPosition(int newX, int newY)
{
	//guarda la pos anterior
	prevX = x;
	prevY = y;
	//y setea la nueva
	x = newX;
	y = newY;
}

int Entity::getX() const
{
	return x;
}

int Entity::getY() const
{
	return y;
}

bool Entity::isActive() const
{
	return active;
}

void Entity::deactivate()
{
	active = false;
}
