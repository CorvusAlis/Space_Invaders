#include <conio2.h>

#include "Player.h"
#include "Bullet.h"

Player::Player(int startX, int startY, int screenW)
	: Entity(startX, startY, '^', LIGHTGREEN)	//pasaje por parametro de los valores de Player - "valores iniciales"
{
	speed = 1;	//se mueve "de a un lugar" (un caracter) por la pantalla
	lives = 3;
	screenWidth = screenW;
	shotCooldownMs = 300;
	lastShotTime = 0;
}

//movimiento

void Player::update(Bullet bullets[], int& bulletCount, int maxBullets)
{
	if (kbhit())
	{
		char key = getch();
		
		if (key == 'a' || key == 'A')
			moveLeft();
		
		if (key == 'd' || key == 'D')
			moveRight();
		
		if (key == ' ')
			shoot(bullets, bulletCount, maxBullets);
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

bool Player::canShoot()	//evita que se spameen disparos agregando un cooldown
{
	clock_t now = clock();
	
	double elapsedMs =
		1000.0 * (now - lastShotTime) / CLOCKS_PER_SEC;
	
	return elapsedMs >= shotCooldownMs;
}

void Player::shoot(Bullet bullets[], int& bulletCount, int maxBullets)
{
	if (!canShoot())
		return;
	
	if (bulletCount >= maxBullets)
		return;
	
	for (int i = 0; i < maxBullets; i++)
	{
		if (!bullets[i].isActive())
		{
			bullets[i] = Bullet(x, y - 1, -1);
			lastShotTime = clock();
			break;
		}
	}
}

//vidas
int Player::getLives() const
{
	return lives;
}

void Player::loseLife()
{
	lives--;
}
