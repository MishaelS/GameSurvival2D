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

float Entity::getRadius() const {
	return GameObject::getRadius();
}

float Entity::getRadiusHitbox(float ratio) const {
	return GameObject::getRadius() / ratio;
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

void Entity::isCollision(Entity* entity) {
	float distance = Vector2Distance(this->getPosition(), entity->getPosition()); // Вычисляем расстояние между центрами сущностей
	float radiusSum = this->getRadiusHitbox(2.f) + entity->getRadiusHitbox(2.f);  // Вычисляем сумму радиусов

	// Если расстояние меньше суммы радиусов, происходит столкновение
	if (distance <= radiusSum) {
		Vector2 normal = Vector2Normalize(Vector2Subtract(this->getPosition(), entity->getPosition())); // Вычисляем вектор нормали от одной сущности к другой
		float penetrationDepth = radiusSum - distance; // Глубина проникновения (насколько одна сущность "вошла" в другую)
		
		// Не дает двигаться той сущности которая производит на него действие //
		// .. хорошая механимка но не то .. //
		// Сдвигаем текущую сущность на безопасное расстояние
		// this->setPosition(Vector2Add(this->getPosition(), Vector2Scale(normal, penetrationDepth)));
		
		
		// Реализация двежение сущности которая производит действие //
		// .. эта реализация больше подходит проекту .. //
		// Сдвигаем обе сущности на половину глубины проникновения
		this->setPosition(Vector2Add(this->getPosition(), Vector2Scale(normal, penetrationDepth * 0.5f)));
		entity->setPosition(Vector2Subtract(entity->getPosition(), Vector2Scale(normal, penetrationDepth * 0.5f)));
	}
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
	
	DrawCircleV(this->getPosition(), 1.f, RED);
}
