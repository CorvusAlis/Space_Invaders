#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity	//la clase Player se deriva de la clase Entity - por eso se puede usar mas adelante start, startY, update(), etc
{
private:
	int speed;
	int lives;
	int screenWidth;	//para no salirse de los bordes de la pantalla
	
public:
	Player(int startX, int startY, int screenW);
	
	void update() override;
	void moveLeft();
	void moveRight();
	
	int getLives() const;
	void loseLife();
};

#endif
