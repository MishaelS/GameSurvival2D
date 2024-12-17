#include "camera_controller.h"

CameraController::CameraController(Vector2 position, Vector2 center, float deadZone, float smoothness)
:	position(position),
	center(center),
	deadZone(deadZone),
	smoothness(smoothness) {
	
		this->camera.target = this->position;
		this->camera.offset = this->center;
		this->camera.rotation = 0.f;
		this->camera.zoom = 1.f;
		
		this->target = this->position;
}

CameraController::~CameraController() {
	// destructor		
}

void CameraController::checkWorldBounds(int worldWidth, int worldHeight) {
	if (this->camera.target.x < CameraDeadZone) {
		this->camera.target.x = CameraDeadZone;
	} else if (this->camera.target.x > worldWidth - CameraDeadZone) {
		this->camera.target.x = worldWidth - CameraDeadZone;
	}
	
	if (this->camera.target.y < CameraDeadZone) {
		this->camera.target.y = CameraDeadZone;
	} else if (this->camera.target.y > worldHeight - CameraDeadZone) {
		this->camera.target.y = worldHeight - CameraDeadZone;
	}
}

Vector2 CameraController::checkDeadZone() {
	if (this->position.x < this->target.x - this->deadZone) {
		this->target.x = this->position.x + this->deadZone;
	} else if (this->position.x > this->target.x + this->deadZone) {
		this->target.x = this->position.x - this->deadZone;
	}
	
	if (this->position.y < this->target.y - this->deadZone) {
		this->target.y = this->position.y + this->deadZone;
	} else if (this->position.y > this->target.y + this->deadZone) {
		this->target.y = this->position.y - this->deadZone;
	}
	
	return this->target;
}

void CameraController::movement() {
	Vector2 cameraTarget = checkDeadZone();
	
	this->camera.target.x += (cameraTarget.x - this->camera.target.x) / this->smoothness;
	this->camera.target.y += (cameraTarget.y - this->camera.target.y) / this->smoothness;

	this->camera.target.x = roundf(this->camera.target.x * 100.f) / 100.f;
	this->camera.target.y = roundf(this->camera.target.y * 100.f) / 100.f;
}

void CameraController::update() {
	this->movement();
	this->checkWorldBounds(WorldWidth, WorldHeight);
}

void CameraController::setZoom(float zoom) {
	this->camera.zoom = zoom;
}

void CameraController::setPosition(Vector2 position) {
	this->position = position;
}

Camera2D CameraController::getCamera() const {
	return this->camera;
}
