#include "scene.h"

// Определение глобальных переменных
EntityValues PlayerValues = {
	{WorldWidth  * (TileSize * TileScale) / 2.f,
	 WorldHeight * (TileSize * TileScale) / 2.f},
	"playerSpriteSheet",
	32, 32,
	186.f,
	0.20f
};

MobValues CowValues = {
	{WorldWidth  * (TileSize * TileScale) / 2.f,
	 WorldHeight * (TileSize * TileScale) / 2.f},
	"cowSpriteSheet",
	32, 32,
	68.f,
	0.24f
};

MobValues ChichenValues = {
	{WorldWidth  * (TileSize * TileScale) / 2.f,
	 WorldHeight * (TileSize * TileScale) / 2.f},
	"chickenSpriteSheet",
	16, 16,
	68.f,
	0.24f
};

CameraValues CValues = {
	{WorldWidth  * (TileSize * TileScale) / 2.f,
	 WorldHeight * (TileSize * TileScale) / 2.f},
	{ScreenWidth  / 2.f,
	 ScreenHeight / 2.f},
	64.f,
	16.f
};

Scene::Scene()
:	maxMobs(256) {
	// Загрузка конфигурация
	this->resourceManager.loadConfig("config.json");
	
	this->level = new Level(64, 64, 16);
	this->level->generate();
	
	// Создаем игрока
	this->player = new Player(
		PlayerValues.position,
		resourceManager.loadTexture(PlayerValues.textureName),
		PlayerValues.frameWidth,
		PlayerValues.frameHeight,
		PlayerValues.moveSpeed,
		PlayerValues.animSpeed
	);
	
	// Создаем контроллер камеры
	this->cameraController = new CameraController(
		CValues.position,
		CValues.centerScreen,
		CValues.deadZone,
		CValues.smoothness
	);
	
	this->addEntity(this->player);
	this->cameraController->setZoom(0.5f);
}

Scene::~Scene() {
	delete this->level;
	delete this->player;
	delete this->cameraController;
	
	for (Entity* entity : this->entities) {
		delete entity;
	}
	
	resourceManager.unloadAllResources();
}

int Scene::countMobs() const {
	int count = 0;
	for (Entity* entity : this->entities) {
		if (dynamic_cast<Mob*>(entity) != nullptr) {
			count++;
		}
	}
	return count;
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

void Scene::collisionEntity(Entity* entity) {
	// Пока не работает
	this->player->isCollision(entity);
}

bool Scene::isEntityVisible(Entity* entity, const Camera2D& camera) {
	// Получаем позицию и радиус объекта
	Vector2 position = entity->getPosition();
	float radius = entity->getRadius();
	
	// Вычисляем видимую область камеры
	Rectangle visibleArea = {
		camera.target.x - ScreenWidth / 2 / camera.zoom,
		camera.target.y - ScreenHeight / 2 / camera.zoom,
		ScreenWidth / camera.zoom,
		ScreenHeight / camera.zoom
	};
	
	// Проверяем, находится ли объект в видимой области
	return CheckCollisionCircleRec(position, radius, visibleArea);
}

void Scene::handleInput() { // Обработка ввода
	// Обрабатываем ввод пользователя
	this->player->management();
	
	if (IsKeyPressed(KEY_P)) {
		if (countMobs() < maxMobs) { // Проверяем, не превышен ли лимит мобов
			this->addEntity(new Mob(
				this->player->getPosition(),
				resourceManager.loadTexture(CowValues.textureName),
				CowValues.frameWidth,
				CowValues.frameHeight,
				CowValues.moveSpeed,
				CowValues.animSpeed
			));
		}
	} else if (IsKeyPressed(KEY_O)) {
		if (countMobs() < maxMobs) { // Проверяем, не превышен ли лимит мобов
			this->addEntity(new Mob(
				this->player->getPosition(),
				resourceManager.loadTexture(ChichenValues.textureName),
				ChichenValues.frameWidth,
				ChichenValues.frameHeight,
				ChichenValues.moveSpeed,
				ChichenValues.animSpeed
			));
		}
	}
}

void Scene::update(float deltaTime) {  // Обновление сцены
	// Обновляем камеру, чтобы она следовала за игроком
	this->cameraController->setPosition(this->player->getPosition());
	this->cameraController->update();
	
	// Обновляем все сущности
	for (Entity* entity : this->entities) {
		if (this->isEntityVisible(entity, this->cameraController->getCamera())) {
			this->collisionEntity(entity);
			entity->update(deltaTime);	
		}
	}
}

void Scene::render() { // Отрисовка сцены
	// Сортируем сущности по координате Y, а если Y равны, то по X
	std::sort(this->entities.begin(), this->entities.end(), [](Entity* entityA, Entity* entityB) {
		if (entityA->getPosition().y == entityB->getPosition().y) {
			return entityA < entityB; // Сортируем по X, если Y равны
		}
		
		return entityA->getPosition().y < entityB->getPosition().y; // Иначе сортируем по Y
	});
	
	BeginMode2D(cameraController->getCamera());
		// Отрисовываем мир
		this->level->render();
		
		// Отрисовываем все сущности
		for (Entity* entity : this->entities) {
			if (isEntityVisible(entity, this->cameraController->getCamera())) {
				entity->render();
			}
		}
		
		// ... Сетка карты ... //
		for (int x = 0; x < WorldWidth * (TileSize * TileScale); x += (TileSize * TileScale)) {
			DrawLine(x, 0, x, WorldWidth * (TileSize * TileScale), {255, 255, 255, 64});
		}
		for (int y = 0; y < WorldHeight * (TileSize * TileScale); y += (TileSize * TileScale)) {
			DrawLine(0, y, WorldHeight * (TileSize * TileScale), y, {255, 255, 255, 64});
		}
		
		DrawCircleV(cameraController->getCamera().target, 2.f, RED);
	EndMode2D();
}

