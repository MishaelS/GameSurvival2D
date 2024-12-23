#include "includes.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity(	Vector2 position,
			Texture2D spriteSheet,
			int frameWidth,
			int frameHeight,
			float movementSpeed = 100.f );
	virtual ~Entity();
	
	Vector2 getPosition() const;
	void setPosition(Vector2 position);
	
	virtual void update(float deltaTime);
	virtual void render();

protected:
	virtual void updateState();	// Методы для управления состоянием
	virtual void updateAnimation(float deltaTime);
	virtual void updateMovement(float deltaTime);
	
	// Поля для управления состоянием и анимацией
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
	float movementSpeed;
	
	Texture2D spriteSheet;
	Rectangle frameRect;
	
	AnimationData currAnimation;
	float animationTimer;
	
	float scale;
};

#endif
