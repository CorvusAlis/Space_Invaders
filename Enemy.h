#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(int startX, int startY, char sprite, int color);
	
	//este metodo es necesario para volverlo una clase no abstracta sobreescribiendo el metodo update de entity
	void update() override{} ; //no tiene logica de movimiento - la linea de enemigos se mueve junta
};
