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

//cambio en el metodo para coorregir incosistencias visuales al momento de colisionar
//si bien la logica update-clear-draw deberia funcionar, no logro que ande con las colisiones
//este deactivate queda mas como un parche forzado
void Entity::deactivate()
{
	//al desactivar, limpiar tambien la posicion actual para evitar sprites "congelados"
	gotoxy(x, y);
	putch(' ');
	
	if (prevX != x || prevY != y)
	{
		gotoxy(prevX, prevY);
		putch(' ');
	}
	
	//sincronizar prev para que clear() no borre una celda incorrecta/vieja
	prevX = x;
	prevY = y;
	
	active = false;
}
