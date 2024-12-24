#include "scene.h"

// Определение глобальных переменных
EntityValues PValues = {
	{WorldWidth * (TileSize * TileScale) / 2.f,
	WorldHeight * (TileSize * TileScale) / 2.f},
	"playerSpriteSheet",
	48,
	48,
	86.f
};

CameraValues CValues = {
	{WorldWidth * (TileSize * TileScale) / 2.f,
	WorldHeight * (TileSize * TileScale) / 2.f},
	{ScreenWidth / 2.f,
	ScreenHeight / 2.f},
	64.f,
	16.f
};

Scene::Scene(int worldW, int worldH, int tileSize, int chunkSize) {
	// Загрузка конфигурация
	this->resourceManager.loadConfig("config.json");
	
	// Создание мира
	// this->world = new World(worldW, worldH, tileSize, chunkSize);
	// this->world->generate();
	
	// Создаем игрока
	this->player = new Player(
		PValues.position,
		resourceManager.loadTexture(PValues.textureName),
		PValues.frameWidth,
		PValues.frameHeight,
		PValues.moveSpeed
	);
	
	// Создаем контроллер камеры
	this->cameraController = new CameraController(
		CValues.position,
		CValues.centerScreen,
		CValues.deadZone,
		CValues.smoothness
	);
	
	this->addEntity(this->player);
}

Scene::~Scene() {
	delete this->world;
	delete this->player;
	delete this->cameraController;
	
	for (Entity* entity : this->entities) {
		delete entity;
	}
	
	resourceManager.unloadAllResources();
}

void Scene::addEntity(Entity* entity) { // Метод для добавления сущности
	this->entities.push_back(entity);
}

void Scene::removeEntity(Entity* entity) { // Метод для удаления сущности
	auto it = std::find(this->entities.begin(), this->entities.end(), entity);
	if (it != this->entities.end()) {
		this->entities.erase(it);
		delete entity; // Освобождаем память
	}
}

void Scene::handleInput() { // Обработка ввода
	// Обрабатываем ввод пользователя
	this->player->management();
}

void Scene::update(float deltaTime) {  // Обновление сцены
	// Обновляем камеру, чтобы она следовала за игроком
	this->cameraController->setPosition(this->player->getPosition());
	this->cameraController->update();
	
	// Обновляем все сущности
	for (Entity* entity : this->entities) {
		entity->update(deltaTime);
	}
}

void Scene::render() { // Отрисовка сцены
	BeginMode2D(cameraController->getCamera());
		// Отрисовываем мир
		// this->world->render(this->cameraController->getCamera());
		
		// Отрисовываем все сущности
		for (Entity* entity : this->entities) {
			entity->render();
		}
		
		DrawCircleV(cameraController->getCamera().target, 2.f, RED);
	EndMode2D();
}

