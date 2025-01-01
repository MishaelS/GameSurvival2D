#include "other.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
	Level(int width, int height, int tileSize);
	~Level();
	
	void generate(); // Генерация уровня
	void render(); // Отрисовка уровня

private:
	int width;
	int height;
	int tileSize;
	
	// Основные тайлы
	std::vector<std::vector<TileType>> tiles;
	
	// Отдельные массивы для сложных объектов
	std::vector<std::vector<int>> tilesTrees; // Деревья (1 - есть дерево, 0 - нет)
	std::vector<std::vector<int>> tilesStone; // Камень  (1 - есть камень, 0 - нет)
	
	// Текстуры
	Texture2D waterTexture;
	Texture2D sandTexture;
	Texture2D grassTexture;
	Texture2D treeTexture;
	Texture2D stoneTexture;
	
	// Генерация шума
	FastNoiseLite noiseGenerator;
	
	// Вспомогательные методы
	void loadTextures();
	void generateTerrain();
	void generateObjects();
};

#endif
