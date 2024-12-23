#include "world.h"

World::World(int width, int height, int tileSize)
:	width(width),
	height(height),
	tileSize(tileSize) {

	this->tilesGrass.resize(width, std::vector<int>(height, 0));
	this->tilesTrees.resize(width, std::vector<int>(height, 0));
	this->grassTileset = LoadTexture("assets/Tilesets/GrassTileset.png"); // Загружаем Tileset
	this->treeTileset  = LoadTexture("assets/Tilesets/TreeTileset.png"); // Загружаем Tileset для деревьев

	// Настройка генератора шума
	this->noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	this->noiseGenerator.SetFrequency(0.05f); // Устанавливаем частоту шума
}

World::~World() {
	UnloadTexture(this->grassTileset);
	UnloadTexture(this->treeTileset);
}

void World::generate() {
	
	FastNoiseLite treeNoiseGenerator;
	treeNoiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	treeNoiseGenerator.SetFrequency(0.1f); // Устанавливаем частоту шума для деревьев
	
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			// Генерация высоты с использованием Perlin Noise
			float noiseValue = 0.0f;
			
			// Добавляем несколько слоев шума с разными частотами и амплитудами
			noiseValue += this->noiseGenerator.GetNoise((float)x, (float)y) * 0.5f;
			
			// Определение типа тайла в зависимости от высоты
				 if (noiseValue < -0.08f) { this->tilesGrass[x][y] = 0; } // Вода
			else if (noiseValue < 0.4f) { this->tilesGrass[x][y] = 1; } // Трава
			
			// Генерация деревьев
			if (this->tilesGrass[x][y] == 1) {
				float treeNoise = treeNoiseGenerator.GetNoise((float)x, (float)y) * 0.6f;
				if (treeNoise > -0.1f) {
					this->tilesTrees[x][y] = 1; // Дерево
				}
			}
		}
	}
}

int World::getTileState(int x, int y, std::vector<std::vector<int>> tiles) {
	// Проверяем соседей тайла
	bool up = (y > 0 && tiles[x][y - 1] == 1);
	bool down = (y < this->height - 1 && tiles[x][y + 1] == 1);
	bool left = (x > 0 && tiles[x - 1][y] == 1);
	bool right = (x < this->width - 1 && tiles[x + 1][y] == 1);
	
	// Проверка углов
	bool cornerUR = (y > 0 && x < this->width - 1 && tiles[x + 1][y - 1] == 0); // Верхний правый угол
	bool cornerUL = (y > 0 && x > 0 && tiles[x - 1][y - 1] == 0); // Верхний левый угол
	bool cornerDR = (y < this->height - 1 && x < this->width - 1 && tiles[x + 1][y + 1] == 0); // Нижний правый угол
	bool cornerDL = (y < this->height - 1 && x > 0 && tiles[x - 1][y + 1] == 0); // Нижний левый угол
	
	// Возвращаем индекс текстуры в зависимости от состояния
	if (up && down && left && right) return 0; // Центральный тайл
	
	if (up && down && left) return 1; // Соединение сверху, снизу и слева
	if (up && down && right) return 2; // Соединение сверху, снизу и справа
	if (up && left && right) return 3; // Соединение сверху, слева и справа
	if (down && left && right) return 4; // Соединение снизу, слева и справа
	
	if (up && left) return 5; // Верхний левый угол
	if (up && right) return 6; // Верхний правый угол
	if (down && left) return 7; // Нижний левый угол
	if (down && right) return 8; // Нижний правый угол
	if (up && down) return 9; // Соединение сверху и снизу
	if (left && right) return 10; // Соединение слева и справа
	
	if (up) return 11; // Соединение сверху
	if (down) return 12; // Соединение снизу
	if (left) return 13; // Соединение слева
	if (right) return 14; // Соединение справа
	
	// Угловые состояния
	if (cornerUR) return 16; // Верхний правый угол
	if (cornerUL) return 17; // Верхний левый угол
	if (cornerDR) return 18; // Нижний правый угол
	if (cornerDL) return 19; // Нижний левый угол
	
	return 15; // Одиночный тайл
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
			
			if (this->tilesGrass[x][y] == 1) {
				// Определяем состояние тайла
				int tileState = getTileState(x, y, this->tilesGrass);
				
				// Вычисляем координаты текстуры в Tileset
				int tileX = (tileState % 5) * this->tileSize;
				int tileY = (tileState / 5) * this->tileSize;
				
				// Отрисовка тайла с использованием DrawTexturePro
				// Отрисовка тайла
				DrawTextureRec(
					this->grassTileset,
					{(float)tileX, (float)tileY, (float)this->tileSize, (float)this->tileSize},
					position,
					WHITE
				);
			}
			
			// Отрисовка деревьев
			if (this->tilesTrees[x][y] == 1) {
				// Определяем состояние тайла
				int tileState = getTileState(x, y, this->tilesTrees);
				
				// Вычисляем координаты текстуры в Tileset
				int tileX = (tileState % 5) * this->tileSize;
				int tileY = (tileState / 5) * this->tileSize;
				
				DrawTextureRec(
					this->treeTileset,
					{(float)tileX, (float)tileY, (float)this->tileSize, (float)this->tileSize},
					position,
					WHITE
				);
			}
		}
	}
}
