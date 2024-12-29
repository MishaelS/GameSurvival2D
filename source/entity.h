#include "other.h"
#include "game_object.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity : GameObject {
public:
	Entity(	Vector2 position,
			Texture2D spriteSheet,
			int frameWidth,
			int frameHeight,
			float movementSpeed  = 86.f,
			float animationSpeed = 0.20f );
	virtual ~Entity();
	
	virtual float getRadius(float ratio = 2.5f) const override;
	
	virtual Vector2 getPosition() const override;
	virtual Vector2 getVelocity() const override;
	virtual Vector2 getDirection() const override;
	
	virtual void setPosition(Vector2 position) override;
	virtual void setVelocity(Vector2 velocity) override;
	virtual void setDirection(Vector2 direction) override;
	
	virtual void update(float deltaTime);
	virtual void render();

protected:
	virtual Vector2 isCollision(Vector2 position, float radius);
	
	virtual void updateState();	// Методы для управления состоянием
	virtual void updateAnimation(float deltaTime);
	virtual void updateMovement(float deltaTime);
	
	// Поля для управления состоянием и анимацией
	bool isAttack;
	Color colorHitbox;
	
	AnimationData currAnimation;
	float animationTimer;
};

#endif
