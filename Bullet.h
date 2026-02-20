#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
private:
	int direction;   //-1 = hacia arriba, +1 = hacia abajo - tanto el jugador como los enemigos usaran bullet, pero en direcciones distintas
	int speed;
	bool active;
	
public:
	
	Bullet();
	Bullet(int startX, int startY, int dir);
	
	void update() override;
	
	void setDirection(int dir);
};

#endif
