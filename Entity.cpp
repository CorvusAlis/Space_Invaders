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
	//borra la celda previa y, si difiere, tambien la actual.
	//esto mantiene la limpieza consistente con deactivate().
	if (prevX >= 1 && prevY >= 1)
	{
		gotoxy(prevX, prevY);
		putch(' ');
	}

	if ((prevX != x || prevY != y) && x >= 1 && y >= 1)
	{
		gotoxy(x, y);
		putch(' ');
	}
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
	//al desactivar, limpiar la posicion actual y tambien la previa.
	//esto evita que queden restos visuales cuando una entidad se desactiva
	//antes de que el loop principal llegue a clear().
	if (x >= 1 && y >= 1)
	{
		gotoxy(x, y);
		putch(' ');
	}

	if ((prevX != x || prevY != y) && prevX >= 1 && prevY >= 1)
	{
		gotoxy(prevX, prevY);
		putch(' ');
	}

	//sincronizar prev para que clear() no intente borrar una celda vieja
	prevX = x;
	prevY = y;

	active = false;
}
