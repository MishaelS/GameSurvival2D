#include "includes.h"

#include "camera_controller.h"
#include "resource_manager.h"

#include "world.h"
#include "player.h"

int main(int argc, char** argv) {
	
	InitWindow(ScreenWidth, ScreenHeight, "Mini-Step");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);
	
	ResourceManager resourceManager;
	resourceManager.loadConfig("config.json");
	
	World world(WorldWidth, WorldHeight, TileSize, 16);
	world.generate();
	
	Vector2 playerPosition = {
		WorldWidth  * TileSize / 2.f,
		WorldHeight * TileSize / 2.f
	};
	Texture2D playerTexture = resourceManager.loadTexture("playerSpriteSheet");
	
	Player player(playerPosition, playerTexture, 48, 48, 86.f);
	
	Vector2 centerScreen = {ScreenWidth / 2.f, ScreenHeight / 2.f};
	CameraController camera(playerPosition, centerScreen, CameraDeadZone, CameraSmoothness);
//	camera.setZoom(0.2f);
	
	while (!WindowShouldClose()) {
		
		player.update(GetFrameTime());
		
		camera.setPosition(player.getPosition());
		camera.update();
		
		BeginDrawing();
			ClearBackground({0, 149, 182, 255});
			
			BeginMode2D(camera.getCamera());
				world.render(camera.getCamera());
				player.render();
				DrawCircleV(camera.getCamera().target, 2.f, RED);
			EndMode2D();
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);
		EndDrawing();
	}
	
	resourceManager.unloadAllResources();
	CloseWindow();
	
	return 0;
}
