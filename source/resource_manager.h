#include "includes.h"

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class ResourceManager {
public:
	void loadConfig(const std::string& configPath);
	void createDefaultConfig(const std::string& configPath);
	
	Texture2D loadTexture(const std::string& textureName);
	Sound loadSound(const std::string& soundName);
	
	void unloadAllResources();
	
private:
	std::unordered_map<std::string, Texture2D> textures;
	std::unordered_map<std::string, Sound> sounds;
	nlohmann::json config;
};

#endif
