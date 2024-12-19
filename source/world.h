#include "includes.h"

#ifndef WORLD_H
#define WORLD_H

class World {
public:
	World(int width, int height, int tileSize);
	~World();
	
	void generate();
	void render(Camera2D camera);
	
private:
	int width;
	int height;
	int tileSize;
	
	std::vector<std::vector<int>> tiles;
	Texture2D grassTexture;
	Texture2D waterTexture;

};

#endif
