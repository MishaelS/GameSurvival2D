#include "includes.h"

#ifndef OTHER_H
#define OTHER_H

// Перечисление типо тайлов для растоновки мира
enum TileType {
	TILE_EMPTY, // Пустоа
	TILE_WATER, // Вода
	TILE_SAND,  // Песок
	TILE_GRASS, // Трава
	TILE_TREE,	// Дерево
	TILE_STONE  // Камень
};

struct Chunk {
	std::vector<std::vector<int>> tilesGrass; // Массив тайлов травы
	std::vector<std::vector<int>> tilesTrees; // Массив тайлов деревьев
	
	Chunk(int chunkSize) {
		tilesGrass.resize(chunkSize, std::vector<int>(chunkSize, 0));
		tilesTrees.resize(chunkSize, std::vector<int>(chunkSize, 0));
	}
};

// Структура значений для игрока
// надо реализовать один общую структуру для всех сущнастей
// а потом уже перенозначать данные... 
struct EntityValues {
	Vector2 position;
	std::string textureName;
	int frameWidth;
	int frameHeight;
	float moveSpeed;
	float animSpeed;
};

struct MobValues {
	Vector2 position;
	std::string textureName;
	int frameWidth;
	int frameHeight;
	float moveSpeed;
	float animSpeed;
};

struct CameraValues {
	Vector2 position;
	Vector2 centerScreen;
	float deadZone;
	float smoothness;
};

// Объявление переменных с использованием extern
extern EntityValues PValues;
extern CameraValues CValues;

// ======================================================== //
// ------------ // Перечисления и структуры // ------------ //
// .......... для рабыта анимации всех сущносте ........... //
// ............. радителя и дочерних классов .............. //
// ======================================================== //

// Состояние направление взгляда сущьности для анимации
// SpriteSheet направление взгляда сущьности расположенны вертикально
enum DirectionState {
	DOWN,
	RIGHT,
	LEFT,
	UP
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
