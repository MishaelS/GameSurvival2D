#include "entity.h"

Entity::Entity(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed)
:	position(position),
	velocity({0.f, 0.f}),
	direction({0.f, 0.f}),
	movementSpeed(movementSpeed),
	isAttack(false),
	spriteSheet(spriteSheet),
	animationTimer(0.f),
	scale(TileScale) {
	
	this->currAnimation = {IDLE, DOWN, 0, 1, 0, 0.22f};
	this->frameRect = {0, 0, (float)frameWidth, (float)frameHeight};
}

Entity::~Entity() {
	// destructor
}

Vector2 Entity::getPosition() const {
	return this->position;
}

void Entity::setPosition(Vector2 position) {
	this->position = position;
}

void Entity::updateState() {
	// Обновление состояния анимации
	if (this->direction.x == 0 && this->direction.y == 0) {
		if (isAttack) {
			this->currAnimation.actionState = ATTACKING;
		} else {
			this->currAnimation.actionState = IDLE;
		}
	}
	else { this->currAnimation.actionState = WALKING; }
	
	// Обновление направления взгляда
		 if (this->direction.x > 0) { this->currAnimation.directState = RIGHT; }
	else if (this->direction.x < 0) { this->currAnimation.directState = LEFT;  }
	else if (this->direction.y > 0) { this->currAnimation.directState = DOWN;  }
	else if (this->direction.y < 0) { this->currAnimation.directState = UP;    }
}

void Entity::updateAnimation(float deltaTime) {
	// Обновление кадра анимации
	this->animationTimer += deltaTime;
	
	if (this->animationTimer >= this->currAnimation.frameDuration) {
		this->animationTimer = 0.f;
		
		if (this->currAnimation.currentFrame <  this->currAnimation.actionState ||
			this->currAnimation.currentFrame >= this->currAnimation.actionState + this->currAnimation.frameCount) {
			this->currAnimation.currentFrame = this->currAnimation.actionState - 1;
		}
		
		this->currAnimation.currentFrame++;
	}
	
	this->frameRect.x = this->currAnimation.currentFrame * this->frameRect.width;
	this->frameRect.y = this->currAnimation.directState * this->frameRect.height;
}

void Entity::updateMovement(float deltaTime) {
	// Обновление позиции
	this->velocity.x = this->movementSpeed * this->direction.x * deltaTime;
	this->velocity.y = this->movementSpeed * this->direction.y * deltaTime;
	
	this->position.x += this->velocity.x;
	this->position.y += this->velocity.y;
}

void Entity::update(float deltaTime) {
	this->updateState();
	this->updateAnimation(deltaTime);
	this->updateMovement(deltaTime);
}

void Entity::render() {
	// Отрисовка текущего кадра анимации
	DrawTexturePro(
		this->spriteSheet,
		{this->frameRect.x,
		 this->frameRect.y,
		 (float)this->frameRect.width,
		 (float)this->frameRect.height},
		{this->position.x - this->frameRect.width,
		 this->position.y - this->frameRect.height,
		 this->frameRect.width * this->scale,
		 this->frameRect.height * this->scale},
		{0.f, 0.f},
		0.f,
		WHITE
	);
	
	DrawRectangleRec(
		{this->position.x - this->frameRect.width / 2.f,
		 this->position.y - this->frameRect.height / 2.f,
		 this->frameRect.width,
		 this->frameRect.height},
		{255, 255, 255, 25}
	);
}
