#include "player.h"

Player::Player(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed, float animationSpeed)
: Entity(position, spriteSheet, frameWidth, frameHeight, movementSpeed, animationSpeed) {
	// Конструктор
}

Player::~Player() {
	// Деструктор
}

void Player::updateState() {
	Entity::updateState();
}

void Player::updateAnimation(float deltaTime) {
	Entity::updateAnimation(deltaTime);
}

void Player::updateMovement(float deltaTime) {
	Entity::updateMovement(deltaTime);
}

Vector2 Player::isCollision(Vector2 position, float radius) {
	return Entity::isCollision(position, radius);
}

void Player::management() {
	// Управление направлением движения
	// Будет у игрока
	// Движение
	this->setDirection({0.f, 0.f});
	if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_X)) {
		isAttack = true;
	} else {
		isAttack = false;

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { this->setDirection({ 1.f, 0.f}); }
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ) { this->setDirection({-1.f, 0.f}); }
		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ) { this->setDirection({ 0.f, 1.f}); }
		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)   ) { this->setDirection({ 0.f,-1.f}); }
	}
}

void Player::update(float deltaTime) {
	Entity::update(deltaTime);
}

void Player::render() {
	Entity::render();
}

