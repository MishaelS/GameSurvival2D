#include "player.h"

Player::Player(Vector2 position, Texture2D spriteSheet, int frameWidth, int frameHeight, float movementSpeed)
: Entity(position, spriteSheet, frameWidth, frameHeight, movementSpeed) {
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

void Player::management() {
	// Управление направлением движения
	// Будет у игрока
	// Движение
	this->direction = {0.f, 0.f};
	if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_X)) {
		isAttack = true;
	} else {
		isAttack = false;

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { this->direction.x =  1; }
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ) { this->direction.x = -1; }
		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ) { this->direction.y =  1; }
		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)   ) { this->direction.y = -1; }
	}
}

void Player::update(float deltaTime) {
	Entity::update(deltaTime);
}

void Player::render() {
	Entity::render();
}

