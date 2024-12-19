#include "world.h"

World::World(int width, int height, int tileSize)
:	width(width),
	height(height),
	tileSize(tileSize) {
	
	this->tiles.resize(width, std::vector<int>(height, 0));
	
	this->grassTexture = LoadTexture("assets/Tilesets/Grass2.png");
	this->waterTexture = LoadTexture("assets/Tilesets/Water2.png");
}

World::~World() {
	UnloadTexture(this->grassTexture);
	UnloadTexture(this->waterTexture);
}

void World::generate() {
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			this->tiles[x][y] =  rand() % 2;
		}
	}
}

void World::render(Camera2D camera) {
	Rectangle visibleArea = {
		camera.target.x - ScreenWidth / 2 / camera.zoom,
		camera.target.y - ScreenHeight / 2 / camera.zoom,
		ScreenWidth / camera.zoom,
		ScreenHeight / camera.zoom
	};
	
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			Vector2 position = {(float)(x * this->tileSize), (float)(y * this->tileSize)};
			if (position.x + this->tileSize < visibleArea.x || position.x > visibleArea.x + visibleArea.width ||
				position.y + this->tileSize < visibleArea.y || position.y > visibleArea.y + visibleArea.height) {
				continue;
			}
			
//			if (this->tiles[x][y] == 0) {
//				DrawTexture(this->waterTexture, position.x, position.y, WHITE);
//			} else
			if (this->tiles[x][y] == 1) {
				DrawTextureEx(
					this->grassTexture,
					position,
					0.f,
					TileScale,
					WHITE
				);
			}
		}
	}
}
