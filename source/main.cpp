#include "includes.h"
#include "scene.h"

int main(int argc, char** argv) {
	InitWindow(ScreenWidth, ScreenHeight, "Mini-Step");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);
	
	Scene scene(WorldWidth, WorldHeight, TileSize, 16);

	while (!WindowShouldClose()) {
		scene.handleInput();
		scene.update(GetFrameTime());
		
		BeginDrawing();
			ClearBackground({0, 149, 182, 255});
			scene.render();
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);
		EndDrawing();
	}
	
	CloseWindow();
	
	return 0;
}
