#include "entity.h"

Entity::Entity(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed)
:	position(position),
	velocity({0.f, 0.f}),
	direction({0.f, 0.f}),
	movementSpeed(movementSpeed),
	spriteSheet(spriteSheet),
	isAlive(true),
	health(100),
	maxHealth(100),
	animationTimer(0.f),
	color(WHITE),
	rotation(0.f),
	scale(TileScale) {
	
	this->currentAnimation = {0, 0, 0.1f, frameWidth, frameHeight};
	this->frameRect = {0, 0, (float)frameWidth, (float)frameHeight};
	this->hitbox = {position.x, position.y, (float)frameWidth, (float)frameHeight};
}

Entity::~Entity() {
	// destructor
}

void Entity::setPosition(Vector2 position) {
	this->position = position;
}

Vector2 Entity::getPosition() const {
	return this->position;
}

Rectangle Entity::getHitbox() const {
	return this->hitbox;
}

bool Entity::checkCollision(Rectangle other) {
	return CheckCollisionRecs(this->hitbox, other);
}

void Entity::handleCollision(Entity* other) {
	// Handle Collision
}

void Entity::takeDamage(int damage) {
	this->health -= damage;
	if (this->health <= 0) {
		this->health = 0;
		this->isAlive = false;
	}
}

void Entity::heal(int amount) {
	this->health += amount;
	if (this->health > this->maxHealth) {
		this->health = this->maxHealth;
	}
}

void Entity::setAnimation(Animation animation) {
	this->currentAnimation = animation;
	this->animationTimer = 0.f;
	this->frameRect = {0.f, 0.f};
}

void Entity::updateAnimation(float deltaTime) {
	if (this->currentAnimation.frameCount > 0) {
		this->animationTimer += deltaTime;
		if (this->animationTimer >= this->currentAnimation.frameDuration) {
			this->animationTimer = 0.f;
			this->currentAnimation.currentFrame = (this->currentAnimation.currentFrame + 1) % this->currentAnimation.frameCount;
			this->frameRect.x = this->currentAnimation.currentFrame * this->currentAnimation.frameWidth;
		}
	}
}

void Entity::movement(float deltaTime) {
	this->velocity.x = this->movementSpeed * this->direction.x * deltaTime;
	this->velocity.y = this->movementSpeed * this->direction.y * deltaTime;
	
	this->position.x += this->velocity.x;
	this->position.y += this->velocity.y;
	
	this->hitbox.x = this->position.x;
	this->hitbox.y = this->position.y;
}

void Entity::update(float deltaTime) {
	
	this->direction = {0.f, 0.f};
	if (IsKeyDown(KEY_A)) { this->direction.x = -1; }
	if (IsKeyDown(KEY_W)) { this->direction.y = -1; }
	if (IsKeyDown(KEY_D)) { this->direction.x =  1; }
	if (IsKeyDown(KEY_S)) { this->direction.y =  1; }
	
	this->movement(deltaTime);
	this->updateAnimation(deltaTime);
}

void Entity::render() {
	DrawTexturePro(
		this->spriteSheet,
		{this->frameRect.x,
		 this->frameRect.y,
		 static_cast<float>(this->currentAnimation.frameWidth),
		 static_cast<float>(this->currentAnimation.frameHeight)},
		{this->position.x - this->frameRect.width,
		 this->position.y - this->frameRect.height,
		 this->currentAnimation.frameWidth * this->scale,
		 this->currentAnimation.frameHeight * this->scale},
		{0.f, 0.f},
		this->rotation,
		this->color
	);
	
	DrawRectangle(
		this->hitbox.x - (this->frameRect.width / 2.f),
		this->hitbox.y - (this->frameRect.height / 2.f),
		this->hitbox.width,
		this->hitbox.height,
		{255, 255, 255, 25}
	);
}
