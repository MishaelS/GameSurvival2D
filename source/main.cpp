#include "includes.h"
#include "camera_controller.h"
#include "resource_manager.h"
#include "world.h"
#include "entity.h"

int main(int argc, char** argv) {
	
	InitWindow(ScreenWidth, ScreenHeight, "Mini-Step");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);
	
	ResourceManager resourceManager;
	resourceManager.loadConfig("config.json");
	
	World world(WorldWidth, WorldHeight, TileSize);
	world.generate();
	
	Vector2 playerPosition = {(WorldWidth * TileSize) / 2.f, (WorldHeight * TileSize) / 2.f};
	Texture2D playerTexture = resourceManager.loadTexture("playerSpriteSheet");
	
	Entity player(playerPosition, playerTexture, 48, 48, 150.f);
	
	Vector2 centerScreen = {ScreenWidth / 2.f, ScreenHeight / 2.f};
	CameraController camera(playerPosition, centerScreen, CameraDeadZone, CameraSmoothness);
//	camera.setZoom(2.f);
	
	while (!WindowShouldClose()) {
		
		player.update(GetFrameTime());
		
		camera.setPosition(player.getPosition());
		camera.update();
		
		BeginDrawing();
			ClearBackground({25, 25, 25, 255});
			
			BeginMode2D(camera.getCamera());
				world.render(camera.getCamera());
				
				for (int x = 0; x < WorldWidth * TileSize; x += TileSize) {
					DrawLine(x, 0, x, WorldWidth * TileSize, {255, 255, 255, 25});
				}
				for (int y = 0; y < WorldHeight * TileSize; y += TileSize) {
					DrawLine(0, y, WorldHeight * TileSize, y, {255, 255, 255, 25});
				}
				
				player.render();
				DrawCircle(player.getPosition().x, player.getPosition().y, 4.f, WHITE);
			EndMode2D();
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);
		EndDrawing();
	}
	
	resourceManager.unloadAllResources();
	CloseWindow();
	
	return 0;
}
