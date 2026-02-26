#include <conio2.h>

#include "Player.h"
#include "Bullet.h"

Player::Player(int startX, int startY, int screenW)
	: Entity(startX, startY, 'A', LIGHTGREEN)	//pasaje por parametro de los valores de Player - "valores iniciales"
{
	speed = 1;	//se mueve "de a un lugar" (un caracter) por la pantalla
	lives = 3;
	screenWidth = screenW;
	shotCooldownMs = 300;
	lastShotTime = 0;
	
	isInvulnerable = false;
	blinkTimer = 0;
	blinkDuration = 60;   //duracion del eecto, aprox un segundo (60 frames = 1 segundo)
	blinkInterval = 5;    
	originalColor = color;
}

void Player::update()
{
	if (isInvulnerable)
	{
		blinkTimer--;
		
		//alternar colores
		if ((blinkTimer / blinkInterval) % 2 == 0)
			color = RED;
		else
			color = originalColor;
		
		if (blinkTimer <= 0)
		{
			isInvulnerable = false;
			color = originalColor;
		}
	}
}

//se desacopla el manejo de entrada por teclado de la clase update
//evita que el update reciba parametros, solo se ocupa de actualizar estado
void Player::handleInput(char key, Bullet bullets[], int& bulletCount, int maxBullets)
{
	if (key == 'a' || key == 'A')
		moveLeft();
	
	if (key == 'd' || key == 'D')
		moveRight();
	
	if (key == ' ')
		shoot(bullets, bulletCount, maxBullets);
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

//disparo

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

bool Player::canShoot()	//evita que se spameen disparos agregando un cooldown
{
	clock_t now = clock();
	
	double elapsedMs =
		1000.0 * (now - lastShotTime) / CLOCKS_PER_SEC;
	
	return elapsedMs >= shotCooldownMs;
}

//colision con balas
bool Player::checkCollision(const Bullet& bullet)
{
	if (!bullet.isActive())
		return false;
	
	if (bullet.getX() == x && bullet.getY() == y)
		return true;
	
	return false;
}

//vidas
int Player::getLives() const
{
	return lives;
}

void Player::loseLife()
{
	if (isInvulnerable)
		return;
	
	lives--;
	
	isInvulnerable = true;	//para evitar que le afectan balas durante el intervalo
	blinkTimer = blinkDuration;
	
	if (lives <= 0)
		active = false;
}
