#include "resource_manager.h"

void ResourceManager::loadConfig(const std::string& configPath) {
	std::ifstream configFile(configPath);
	if (!configFile.is_open()) {
		std::cerr << "Error: Could not open config file: " << configPath << std::endl;
		std::cerr << "Creating defailt config file . . ." << std::endl;
		this->createDefaultConfig(configPath);
		return;
	}
	
	configFile >> this->config;
}

void ResourceManager::createDefaultConfig(const std::string& configPath) {
	nlohmann::json defaultConfig;
	
	defaultConfig["images"] = {
		{"playerSpriteSheet", "assets/Characters/Basic_Charakter_Spritesheet.png"},
		{"chickenSpriteSheet", "assets/Characters/Free_Chicken_Sprites.png"},
		{"cowSpriteSheet", "assets/Characters/Free_Cow_Sprites.png"}
	};
	
	defaultConfig["sounds"] = {
		{"playerSoundMove", "assets/Sound"},
		{"backgroundMusic", "assets/Sound"}
	};
	
	std::ofstream configFile(configPath);
	if (!configFile.is_open()) {
		std::cerr << "Error: Could not create default config file: " << configPath << std::endl;
		return;
	}
	
	configFile << defaultConfig.dump(4);
	configFile.close();
	
	std::cout << "Default config file created: " << configPath << std::endl;
}

Texture2D ResourceManager::loadTexture(const std::string& textureName) {
	if (this->textures.find(textureName) != this->textures.end()) {
		return this->textures[textureName];
	}
	
	std::string texturePath = this->config["images"][textureName];
	if (texturePath.empty()) {
		std::cerr << "Error: Texture path not found for: " << textureName << std::endl;
		return {0};
	}
	
	Texture2D texture = LoadTexture(texturePath.c_str());
	if (texture.id == 0) {
		std::cerr << "Error: Failed to load texture: " << texturePath << std::endl;
		return {0};
	}
	
	this->textures[textureName] = texture;
	return texture;
}

Sound ResourceManager::loadSound(const std::string& soundName) {
	if (this->sounds.find(soundName) != this->sounds.end()) {
		return this->sounds[soundName];
	}
	
	std::string soundPath = this->config["sounds"][soundName];
	if (soundPath.empty()) {
		std::cerr << "Error: Sound path not found for: " << soundName << std::endl;
		return {0};
	}
	
	Sound sound = LoadSound(soundPath.c_str());
	if (sound.frameCount == 0) {
		std::cerr << "Error: Failed to load sound: " << soundPath << std::endl;
		return {0};
	}
	
	this->sounds[soundName] = sound;
	return sound;
}

void ResourceManager::unloadAllResources() {
	for (auto& [name, texture] : this->textures) {
		UnloadTexture(texture);
	}
	this->textures.clear();
	
	for (auto& [name, sound] : this->sounds) {
		UnloadSound(sound);
	}
	this->sounds.clear();
}
