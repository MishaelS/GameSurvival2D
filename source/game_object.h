#include "other.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
	GameObject( Vector2 position,
				Texture2D spriteSheet,
				int frameWidth,
				int frameHeight,
				float movementSpeed = 86.f );
	virtual ~GameObject();
	
	virtual float getRadius() const;
	
	virtual Vector2 getPosition() const;
	virtual Vector2 getVelocity() const;
	virtual Vector2 getDirection() const;
	
	virtual void setPosition(Vector2 position);
	virtual void setVelocity(Vector2 velocity);
	virtual void setDirection(Vector2 direction);
	
	virtual void render();
	
protected:
	// Поля для управления состоянием и анимацией
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
	float movementSpeed;
	
	Texture2D spriteSheet;
	Rectangle frameRect;
	
	float scale;
};

#endif
