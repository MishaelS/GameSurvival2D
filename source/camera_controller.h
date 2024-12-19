#include "includes.h"

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

class CameraController {
public:
	CameraController(Vector2 position, Vector2 center, float deadZone, float smoothness);
	~CameraController();
	
	void setZoom(float zoom);
	void setPosition(Vector2 position);
	Camera2D getCamera() const;
	
	void update();
	
private:
	void checkWorldBounds(int worldWidth, int worldHeight);
	Vector2 checkDeadZone();
	
	void movement();
	
	Camera2D camera;
	Vector2 position;
	Vector2 target;
	Vector2 center;
	
	float deadZone;
	float smoothness;
};

#endif
