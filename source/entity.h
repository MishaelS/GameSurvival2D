#include "includes.h"

#ifndef ENTITY_H
#define ENTITY_H

struct Animation {
	int frameCount;
	int currentFrame;
	float frameDuration;
	int frameWidth;
	int frameHeight;
};

class Entity {
public:
	Entity(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed = 100.f);
	virtual ~Entity();
	
	void setPosition(Vector2 position);
	Vector2 getPosition() const;
	Rectangle getHitbox() const;
	
	bool checkCollision(Rectangle other);
	void handleCollision(Entity* other);
	
	void takeDamage(int damage);
	void heal(int amount);
	
	void setAnimation(Animation animation);
	void updateAnimation(float deltaTime);
	
	virtual void movement(float deltaTime);
	virtual void update(float deltaTime);
	virtual void render();
	Vector2 direction;

protected:
	Vector2 position;
	Vector2 velocity;
	float movementSpeed;
	
	Texture2D spriteSheet;
	Rectangle frameRect;
	Rectangle hitbox;
	
	bool isAlive;
	int health;
	int maxHealth;
	
	Animation currentAnimation;
	float animationTimer;
	
	Color color;
	float rotation;
	float scale;
};

#endif
