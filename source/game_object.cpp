#include "game_object.h"

GameObject::GameObject(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed)
:	position(position),
	velocity({0.f, 0.f}),
	direction({0.f, 0.f}),
	movementSpeed(movementSpeed),
	spriteSheet(spriteSheet),
	frameRect({0, 0, (float)frameWidth, (float)frameHeight}),
	scale(TileScale) {
	// Конструктор
}

GameObject::~GameObject() {
	// Деструктор
}

float GameObject::getRadius(float ratio) const {
	return (float)(this->frameRect.width + this->frameRect.height) / (this->scale * ratio);
}

Vector2 GameObject::getPosition() const {
	return this->position;
}

Vector2 GameObject::getVelocity() const {
	return this->velocity;
}
Vector2 GameObject::getDirection() const {
	return this->direction;
}

void GameObject::setPosition(Vector2 position) {
	this->position = position;
}

void GameObject::setVelocity(Vector2 velocity) {
	this->velocity = velocity;
}

void GameObject::setDirection(Vector2 direction) {
	this->direction = direction;
}

void GameObject::render() {
	// Отрисовка текущего кадра анимации
	DrawTexturePro(
		this->spriteSheet,
		{this->frameRect.x,
		 this->frameRect.y,
		 (float)this->frameRect.width,
		 (float)this->frameRect.height},
		{this->position.x - this->frameRect.width,
		 this->position.y - this->frameRect.height,
		 this->frameRect.width  * this->scale,
		 this->frameRect.height * this->scale},
		{0.f, 0.f},
		0.f,
		WHITE
	);
}
