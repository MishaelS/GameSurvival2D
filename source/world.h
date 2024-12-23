#include "includes.h"

#ifndef WORLD_H
#define WORLD_H

class World {
public:
	World(int width, int height, int tileSize);
	~World();
	
	void generate();
	void render(Camera2D camera);
	
private:
	// Метод для определения состояния тайла
	int getTileState(int x, int y, std::vector<std::vector<int>> tiles);
	
	int width;
	int height;
	int tileSize;
	
	
	std::vector<std::vector<int>> tilesGrass; // Массив тайлов травы
	std::vector<std::vector<int>> tilesTrees; // Массив тайлов деревьев
	Texture2D grassTileset; // Текстура Tileset для травы
	Texture2D treeTileset;  // Текстура Tileset для деревьев
	
	FastNoiseLite noiseGenerator; // Генератор шума

};

#endif
