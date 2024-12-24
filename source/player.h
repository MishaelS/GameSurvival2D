#include "includes.h"
#include "entity.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Entity {
public:
	Player( Vector2 position,
			Texture2D spriteSheet,
			int frameWidth,
			int frameHeight,
			float movementSpeed = 100.f );
	virtual ~Player();
	
	void management();
	void update(float deltaTime) override;
	void render() override;

private:
	void updateState() override;
	void updateAnimation(float deltaTime) override;
	void updateMovement(float deltaTime) override;
	
};

#endif
