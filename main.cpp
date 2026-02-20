#include <conio2.h>
#include <windows.h>  //para Sleep() - control de frames

#include "Player.h"
#include "Bullet.h"

int main()
{
	int screenWidth = 80;
	int screenHeight = 25;
	
	const int MAX_BULLETS = 50;
	Bullet bullets[MAX_BULLETS];
	int bulletCount = 0;
	
	textbackground(BLACK);
	clrscr();  //solo para inicializar pantalla al inicio
	
	Player player(screenWidth / 2, screenHeight - 2, screenWidth);	//posicionamiento del jugador en la mitad de la pantalla
	
	player.draw();
	
	while (true)
	{
		player.clear();
		player.update(bullets, bulletCount, MAX_BULLETS);
		player.draw();
		Sleep(16);  //60 FPS aproximado
	}
	
	return 0;
}
