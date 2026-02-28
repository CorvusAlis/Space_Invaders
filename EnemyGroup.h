#pragma once

#include "Enemy.h"
#include "Bullet.h"

//esta clase manejara el movimiento de la linea entera de enemigos
//la clase Enemy manejara la creacion de cada enemigo individual, pero no tendra logica de movimiento

class EnemyGroup
{
private:
	static const int ENEMY_COLS = 10;
	static const int ENEMY_ROWS = 4;
	
	Enemy enemies[ENEMY_ROWS][ENEMY_COLS];
	
	int startX;
	int startY;
	int spacing;
	
	int direction;
	int speed;
	int screenWidth;
	
	//para controlar la "velocidad" del movimiento: dejan de moverse todos los frames, se mueven cada X frames.
	//se puede modificar para que cada vez que se mate a un enemigo o se limpie una fila, acelere el movimiento del resto
	int frameDelay;
	int frameCounter;
	
	int initialSpeed;
	
	void initializeEnemies();
	
public:
	EnemyGroup(int startX, int startY, int spacing, int scrWidth);
	
	void clear();
	void update();
	void draw();
	
	bool checkBulletCollision(Bullet& bullet);
	void tryShoot(Bullet enemyBullets[], int maxBullets);
	void increaseSpeed();
	
	bool areEnemiesAlive() const;
	
	void reset();
};
