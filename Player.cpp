#include "Player.h"
#include <conio2.h>

Player::Player(int startX, int startY, int screenW)
	: Entity(startX, startY, '^', LIGHTGREEN)	//pasaje por parametro de los valores de Player - "valores iniciales"
{
	speed = 1;	//se mueve "de a un lugar" por la pantalla
	lives = 3;
	screenWidth = screenW;
}

void Player::update()
{
	if (kbhit())
	{
		char key = getch();
		
		if (key == 'a' || key == 'A')
			moveLeft();
		
		if (key == 'd' || key == 'D')
			moveRight();
	}
}

void Player::moveLeft()
{
	if (x - speed > 1)
	{
		clear();
		setPosition(x - speed, y);
		draw();
	}
}

void Player::moveRight()
{
	if (x + speed < screenWidth)
	{
		clear();
		setPosition(x + speed, y);
		draw();
	}
}

int Player::getLives() const
{
	return lives;
}

void Player::loseLife()
{
	lives--;
}
