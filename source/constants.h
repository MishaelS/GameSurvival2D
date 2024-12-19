#ifndef CONSTANTS_H
#define CONSTANTS_H

const int ScreenWidth  = 800;
const int ScreenHeight = 512;
const int FrameRate    = 60;

const int TileScale = 2;
const int TileSize  = 16 * TileScale;

const int WorldWidth  = 128;
const int WorldHeight = 128;

const float CameraDeadZone = 64.f;
const float CameraSmoothness = 16.f;

struct Animation {
	int frameCount;
	int currentFrame;
	float frameDuration;
	int frameWidth;
	int frameHeight;
};


#endif
