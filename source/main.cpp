#include "includes.h"
#include "camera_controller.h"
#include "resource_manager.h"
#include "entity.h"

int main(int argc, char** argv) {
	
	InitWindow(ScreenWidth, ScreenHeight, "Mini-Step");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);
	
	ResourceManager resourceManager;
	resourceManager.loadConfig("config.json");
	
	Vector2 playerPosition = {WorldWidth / 2.f, WorldHeight / 2.f};
	Texture2D playerTexture = resourceManager.loadTexture("playerSpriteSheet");
	
	Entity player(playerPosition, playerTexture, 48, 48, 300.f);
	
	Vector2 centerScreen = {ScreenWidth / 2.f, ScreenHeight / 2.f};
	CameraController camera(playerPosition, centerScreen, CameraDeadZone, CameraSmoothness);
	
	while (!WindowShouldClose()) {
		player.direction = {0.f, 0.f};
		if (IsKeyDown(KEY_A)) { player.direction.x = -1; }
		if (IsKeyDown(KEY_W)) { player.direction.y = -1; }
		if (IsKeyDown(KEY_D)) { player.direction.x =  1; }
		if (IsKeyDown(KEY_S)) { player.direction.y =  1; }
		
		camera.setPosition(player.getPosition());
		camera.update();
		
		player.update(GetFrameTime());
		
		BeginDrawing();
			ClearBackground({25, 25, 25, 255});
			
			BeginMode2D(camera.getCamera());
				for (int x = 0; x < 128 * GridSize; x += GridSize) {
					DrawLine(x, 0, x, 128 * GridSize, {255, 255, 255, 64});
				}
				for (int y = 0; y < 128 * GridSize; y += GridSize) {
					DrawLine(0, y, 128 * GridSize, y, {255, 255, 255, 64});
				}
				
				player.render();
			EndMode2D();
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);
		EndDrawing();
	}
	
	resourceManager.unloadAllResources();
	CloseWindow();
	
	return 0;
}
