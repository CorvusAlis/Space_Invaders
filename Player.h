#ifndef PLAYER_H
#define PLAYER_H

#include <ctime> 

#include "Entity.h"
#include "Bullet.h"


class Player : public Entity	//la clase Player se deriva de la clase Entity - por eso se puede usar mas adelante start, startY, update(), etc
{
private:
	int speed;
	int lives;
	int screenWidth;	//para no salirse de los bordes de la pantalla
	
	clock_t lastShotTime;
	int shotCooldownMs;
	
	//para efectos visuales cuando colisiona con una bala enemiga
	bool isInvulnerable;
	int blinkTimer;
	int blinkDuration;
	int blinkInterval;
	int originalColor;
	
public:
	Player(int startX, int startY, int screenW);
	
	void update() override;

	void handleInput(char key, Bullet bullets[], int& bulletCount, int maxBullets);
	void moveLeft();
	void moveRight();
	
	//disparos
	bool canShoot();
	void shoot(Bullet bullets[], int& bulletCount, int maxBullets);
	
	//vidas y colisiones
	bool checkCollision(const Bullet& bullet);
	int getLives() const;
	void loseLife();
};

#endif
