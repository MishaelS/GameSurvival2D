#include "other.h"

#include "camera_controller.h"
#include "resource_manager.h"
#include "entity.h"
#include "player.h"
#include "level.h"
#include "mob.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	Scene();
	~Scene();
	
	void handleInput();				// Обработка ввода
	void update(float deltaTime);	// Обновление сцены
	void render();					// Отрисовка сцены

private:
	// Методы для управления сущностями
	void collisionEntity(Entity* entity); // Обработка столкновение
	
	bool isEntityVisible(Entity* entity, const Camera2D& camera);
	
	int countMobs() const;
	void addEntity(Entity* entity);	 	// Добавление сущности
	void removeEntity(Entity* entity);	// Удаление сущности
	
	Level* level;   // Генерация уровня
	Player* player;	// Игрок
	CameraController* cameraController; // Контроллер камеры
	
	std::vector<Entity*> entities; // Список сущностей
	
	ResourceManager resourceManager;
	
	int maxMobs; // Максимальное количество мобов
};

#endif
