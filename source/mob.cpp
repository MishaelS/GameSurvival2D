#include "mob.h"

Mob::Mob(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed, float animationSpeed)
: Entity(position, spriteSheet, frameWidth, frameHeight, movementSpeed, animationSpeed) {
	// Конструктор
}

Mob::~Mob() {
	// Деструктор
}

float Mob::getRadius(float ratio) const {
	return Entity::getRadius(ratio);
}

Vector2 Mob::getPosition() const {
	return Entity::getPosition();
}

Vector2 Mob::getVelocity() const {
	return Entity::getVelocity();
}
Vector2 Mob::getDirection() const {
	return Entity::getDirection();
}

void Mob::setPosition(Vector2 position) {
	Entity::setPosition(position);
}

void Mob::setVelocity(Vector2 velocity) {
	Entity::setVelocity(velocity);
}

void Mob::setDirection(Vector2 direction) {
	Entity::setDirection(direction);
}

void Mob::updateState() {
	Entity::updateState();
}

void Mob::updateAnimation(float deltaTime) {
	Entity::updateAnimation(deltaTime);
}

void Mob::updateMovement(float deltaTime) {
	Entity::updateMovement(deltaTime);
}

void Mob::findingWay() {
	// Поиск пути
}

void Mob::update(float deltaTime) {
	Entity::update(deltaTime);
}

void Mob::render() {
	Entity::render();
}

