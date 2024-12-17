#include "includes.h"

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

class CameraController {
public:
	CameraController(Vector2 position, Vector2 center, float deadZone, float smoothness);
	~CameraController();
	
	void checkWorldBounds(int worldWidth, int worldHeight);
	Vector2 checkDeadZone();
	void movement();
	
	void update();
	void setZoom(float zoom);
	void setPosition(Vector2 position);
	Camera2D getCamera() const;

private:
	Camera2D camera;
	Vector2 position;
	Vector2 target;
	Vector2 center;
	
	float deadZone;
	float smoothness;
};

#endif
