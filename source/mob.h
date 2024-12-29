#include "includes.h"
#include "entity.h"

#ifndef MOB_H
#define MOB_H

class Mob : public Entity {
public:
	Mob( Vector2 position,
		 Texture2D spriteSheet,
		 int frameWidth,
		 int frameHeight,
		 float movementSpeed  = 86.f,
		 float animationSpeed = 0.20f );
	virtual ~Mob();
	
	virtual float getRadius(float ratio = 2.5f) const override;
	
	virtual Vector2 getPosition() const override;
	virtual Vector2 getVelocity() const override;
	virtual Vector2 getDirection() const override;
	
	virtual void setPosition(Vector2 position) override;
	virtual void setVelocity(Vector2 velocity) override;
	virtual void setDirection(Vector2 direction) override;
	
	void findingWay();
	void update(float deltaTime) override;
	void render() override;
	
private:
	void updateState() override;
	void updateAnimation(float deltaTime) override;
	void updateMovement(float deltaTime) override;
};

#endif
