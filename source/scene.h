#include "includes.h"

#include "camera_controller.h"
#include "resource_manager.h"
#include "entity.h"
#include "player.h"
#include "world.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	Scene(int worldW, int worldH, int tileSize, int chunkSize);
	~Scene();
	
	void handleInput();				// Обработка ввода
	void update(float deltaTime);	// Обновление сцены
	void render();					// Отрисовка сцены

private:
	// Методы для управления сущностями
	void addEntity(Entity* entity);	 	// Добавление сущности
	void removeEntity(Entity* entity);	// Удаление сущности
	
	World*  world;	// Ландшафт
	Player* player;	// Игрок
	CameraController* cameraController; // Контроллер камеры
	
	std::vector<Entity*> entities; // Список сущностей
	
	ResourceManager resourceManager;
	
};

#endif
