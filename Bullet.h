#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
private:
	int direction;   //-1 = hacia arriba, +1 = hacia abajo - tanto el jugador como los enemigos usaran bullet, pero en direcciones distintas
	int speed;
	
	int moveDelay;
	int moveTimer;
	
public:
	
	Bullet();
	Bullet(int startX, int startY, int dir);
	Bullet(int startX, int startY, char sprite, int color, int spd, int dir);
	
	void update() override;
	
	void setDirection(int dir);
	
	//getters
	int getX();
	int getY();
};

#endif
