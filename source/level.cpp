#include "level.h"

Level::Level(int width, int height, int tileSize)
: width(width), height(height), tileSize(tileSize) {
	this->tiles.resize(width, std::vector<TileType>(height, TILE_EMPTY));
	this->tilesTrees.resize(width, std::vector<int>(height, 0));
	this->tilesStone.resize(width, std::vector<int>(height, 0));
	
	this->noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	this->noiseGenerator.SetFrequency(0.05f);
	
	this->loadTextures();
}

Level::~Level() {
	UnloadTexture(this->waterTexture);
	UnloadTexture(this->sandTexture);
	UnloadTexture(this->grassTexture);
	UnloadTexture(this->treeTexture);
	UnloadTexture(this->stoneTexture);
}

void Level::generate() {
	this->generateTerrain();
	this->generateObjects();
}

void Level::loadTextures() {
	this->waterTexture = LoadTexture("assets/Tilesets/waterT.png");
	this->sandTexture  = LoadTexture("assets/Tilesets/sandT.png");
	this->grassTexture = LoadTexture("assets/Tilesets/grassT.png");
	this->treeTexture  = LoadTexture("assets/Tilesets/treeT.png");
	this->stoneTexture = LoadTexture("assets/Tilesets/stoneT.png");
}

void Level::generateTerrain() {
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			float noiseValue = this->noiseGenerator.GetNoise((float)x, (float)y);
			
			if (noiseValue < -0.5f) {
				this->tiles[x][y] = TILE_WATER;
			} else if (noiseValue < -0.2f) {
				this->tiles[x][y] = TILE_SAND;
			} else if (noiseValue < 0.2f) {
				this->tiles[x][y] = TILE_GRASS;
			} else {
				this->tiles[x][y] = TILE_STONE;
			}
		}
	}
}

void Level::generateObjects() {
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			// Генерация деревьев на траве
			if (this->tiles[x][y] == TILE_GRASS && this->noiseGenerator.GetNoise((float)x * 2, (float)y * 2) > 0.5f) {
				this->tilesTrees[x][y] = 1;
			}
			
			// Генерация камней на траве
			if (this->tiles[x][y] == TILE_GRASS && tiles[x][y] != TILE_TREE && this->noiseGenerator.GetNoise((float)x * 3, (float)y * 3) > 0.7f) {
				this->tilesStone[x][y] = 1;
			}
		}
	}
}

void Level::render() {
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			Vector2 position = {(float)(x * this->tileSize), (float)(y * this->tileSize)};
			
			// Отрисовка основных тайлов
			switch (this->tiles[x][y]) {
				case TILE_WATER:
					DrawTexture(this->waterTexture, position.x, position.y, WHITE);
					break;
				case TILE_SAND:
					DrawTexture(this->sandTexture, position.x, position.y, WHITE);
					break;
				case TILE_GRASS:
					DrawTexture(this->grassTexture, position.x, position.y, WHITE);
					break;
				case TILE_STONE:
					DrawTexture(this->stoneTexture, position.x, position.y, WHITE);
					break;
			}
			
			// Отрисовка деревьев
			if (this->tilesTrees[x][y] == 1) {
				DrawTexture(this->treeTexture, position.x, position.y, WHITE);
			}
			
			// Отрисовка камней
			if (this->tilesStone[x][y] == 1) {
				DrawTexture(this->stoneTexture, position.x, position.y, WHITE);
			}
		}
	}
}
