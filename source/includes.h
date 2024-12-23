#ifndef INCLUDES_H
#define INCLUDES_H

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
#include "nlohmann/json.hpp"
#include "FastNoiseLite/Cpp/FastNoiseLite.h"

#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "constants.h"

// Перечисление типо тайлов для растоновки мира
enum TileType {
	TILE_EMPTY = 0,	// Пустой тайл
	TILE_GRASS = 1,	// Трава
	TILE_SAND  = 3,	// Песок
	TILE_WATER = 2,	// Вода
	TILE_TREE  = 4,	// Дерево
	TILE_ROCK  = 5	// Камень
};

struct Chunk {
	std::vector<std::vector<int>> tilesGrass; // Массив тайлов травы
	std::vector<std::vector<int>> tilesTrees; // Массив тайлов деревьев
	
	Chunk(int chunkSize) {
		tilesGrass.resize(chunkSize, std::vector<int>(chunkSize, 0));
		tilesTrees.resize(chunkSize, std::vector<int>(chunkSize, 0));
	}
};

// Состояние направление взгляда сущьности для анимации
// SpriteSheet направление взгляда сущьности расположенны вертикально
enum DirectionState {
	DOWN	= 0,
	RIGHT	= 1,
	LEFT	= 2,
	UP		= 3
};

// Состояние действия сущьности для анимации
// SpriteSheet действия сущьности расположенны горезонтально
enum ActionState {
	IDLE		= 0,
	WALKING		= 2,
	RUNNING		= 2,
	ATTACKING	= 4,
//	DEAD		= 0,
//	INTERACTING = 0
};

struct AnimationData {
	ActionState		actionState;
	DirectionState	directState;
	int frameStart;
	int frameCount;
	int currentFrame;
	float frameDuration;
};

#endif
