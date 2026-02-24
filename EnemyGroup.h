#pragma once

#include "Enemy.h"

//esta clase manejara el movimiento de la linea entera de enemigos
//la clase Enemy manejara la creacion de cada enemigo individual, pero no tendra logica de movimiento

class EnemyGroup
{
private:
	static const int MAX_ENEMIES = 10;
	
	Enemy enemies[MAX_ENEMIES];
	
	int direction;
	int speed;
	int screenWidth;
	
	//para controlar la "velocidad" del movimiento: dejan de moverse todos los frames, se mueven cada X frames.
	int frameDelay;
	int frameCounter;
	
public:
	EnemyGroup(int startX, int startY, int spacing, int scrWidth);
	
	void update();
	void draw();
};
