#include "entity.h"

Entity::Entity(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed, float animationSpeed)
: GameObject(position, spriteSheet, frameWidth, frameHeight, movementSpeed),
	isAttack(false),
	colorHitbox({255, 255, 255, 45}),
	currAnimation({IDLE, DOWN, 0, 1, 0, animationSpeed}),
	animationTimer(0.f) {
	// Конструктор
}

Entity::~Entity() {
	// Деструктор
}

float Entity::getRadius(float ratio) const {
	return GameObject::getRadius(ratio);
}

Vector2 Entity::getPosition() const {
	return GameObject::getPosition();
}

Vector2 Entity::getVelocity() const {
	return GameObject::getVelocity();
}
Vector2 Entity::getDirection() const {
	return GameObject::getDirection();
}

void Entity::setPosition(Vector2 position) {
	GameObject::setPosition(position);
}

void Entity::setVelocity(Vector2 velocity) {
	GameObject::setVelocity(velocity);
}

void Entity::setDirection(Vector2 direction) {
	GameObject::setDirection(direction);
}

Vector2 Entity::isCollision(Vector2 position, float radius) {
	float distance = Vector2DistanceSqr(this->getPosition(), position);
	if (distance < (this->getRadius() + radius)) {
		// Корректировка позиций
		Vector2 delta = {this->getPosition().x - position.x, this->getPosition().y - position.y};
		float overlap = (this->getRadius() + radius) - distance;
		
		Vector2 correction = {delta.x / distance * overlap / 2, delta.y / distance * overlap / 2};
		
		this->colorHitbox = {255,   0,   0, 45};
		return {this->getPosition().x - correction.x, this->getPosition().y - correction.y};
	}
	
	this->colorHitbox = {255, 255, 255, 45};
	return this->getPosition();
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
	// Отрисовка граници столкновения
	DrawCircleV(
		this->getPosition(),
		this->getRadius(),
		this->colorHitbox
	);
	
	GameObject::render();
}
