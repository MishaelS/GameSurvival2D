#include "includes.h"

int main(int argc, char** argv) {
	
	InitWindow(ScreenWidth, ScreenHeight, "Mini-Step");
	SetTargetFPS(60);
	
	const float cameraDeadZone = 50.f;
	const float cameraSmoothness = 12.f;
	
	const int gridSize = 32;
	Vector2 playerPosition = {0.f, 0.f};
	Texture2D playerTexture = LoadTexture("default.png");
	
	Camera2D camera = {0};
	Vector2 cameraTarget = {playerPosition.x, playerPosition.y};
	camera.target.x += (cameraTarget.x - camera.target.x) / cameraSmoothness;
	camera.target.y += (cameraTarget.y - camera.target.y) / cameraSmoothness;
	camera.offset = {ScreenWidth / 2.f, ScreenHeight / 2.f};
	camera.rotation = 0.f;
	camera.zoom = 1.f;
	
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_A)) { playerPosition.x -= 200.f * GetFrameTime(); }
		if (IsKeyDown(KEY_W)) { playerPosition.y -= 200.f * GetFrameTime(); }
		if (IsKeyDown(KEY_D)) { playerPosition.x += 200.f * GetFrameTime(); }
		if (IsKeyDown(KEY_S)) { playerPosition.y += 200.f * GetFrameTime(); }
		
		if (playerPosition.x < cameraTarget.x - cameraDeadZone) {
			cameraTarget.x = playerPosition.x + cameraDeadZone;
		} else if (playerPosition.x > cameraTarget.x + cameraDeadZone) {
			cameraTarget.x = playerPosition.x - cameraDeadZone;
		}
		
		if (playerPosition.y < cameraTarget.y - cameraDeadZone) {
			cameraTarget.y = playerPosition.y + cameraDeadZone;
		} else if (playerPosition.y > cameraTarget.y + cameraDeadZone) {
			cameraTarget.y = playerPosition.y - cameraDeadZone;
		}
		
		camera.target.x += (cameraTarget.x - camera.target.x) / cameraSmoothness;
		camera.target.y += (cameraTarget.y - camera.target.y) / cameraSmoothness;
		
		BeginDrawing();
			ClearBackground({25, 25, 25, 255});
			
			BeginMode2D(camera);
				for (int x = 0; x < 128 * gridSize; x += gridSize) {
					DrawLine(x, 0, x, 128 * gridSize, LIGHTGRAY);
					for (int y = 0; y < 128 * gridSize; y += gridSize) {
						DrawLine(0, y, 128 * gridSize, y, LIGHTGRAY);
					}
				}
				
				DrawTexture(playerTexture,
							playerPosition.x - playerTexture.width  / 2.f,
							playerPosition.y - playerTexture.height / 2.f,
							WHITE);
				
			EndMode2D();
			DrawText("Use arrow keys to move!", 10, 10, 20, WHITE);
			
		EndDrawing();
	}
	
	UnloadTexture(playerTexture);
	CloseWindow();
	
	return 0;
}
