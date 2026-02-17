#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
	int x;
	int y;
	
	//para guardar la posicion previa de la entidad y manejar el borrado/dibujado
	int prevX;
	int prevY;
	
	char sprite;
	int color;
	
	//para control de los enemigos, si recibieron un impacto se desactivan
	bool active;
	
public:
	Entity(int startX, int startY, char s, int c);
	virtual ~Entity();
	
	virtual void update() = 0;   // método abstracto
	virtual void draw() const;
	virtual void clear() const;
	
	void setPosition(int newX, int newY);
	
	int getX() const;
	int getY() const;
	
	bool isActive() const;
	void deactivate();
};

#endif
