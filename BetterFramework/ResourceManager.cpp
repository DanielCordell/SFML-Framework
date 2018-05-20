#include <SFML/Graphics/Shader.hpp>
#include "ResourceManager.h"

ResourceManager* ResourceManager::Get() {
	static ResourceManager rm;
	return &rm;
}

template <>
sf::Texture& ResourceManager::GetResource(std::string resourceName) {
	if (textureMap.find(resourceName) == textureMap.end()) {
		textureMap[resourceName].loadFromFile("textures/" + resourceName);
	}
	return textureMap[resourceName];
}

template <>
sf::Music& ResourceManager::GetResource(std::string resourceName) {
	if (musicMap.find(resourceName) == musicMap.end()) {
		musicMap[resourceName].openFromFile("music/" + resourceName);
	}
	return musicMap[resourceName];
}

template <>
sf::SoundBuffer& ResourceManager::GetResource(std::string resourceName) {
	if (soundMap.find(resourceName) == soundMap.end()) {
		soundMap[resourceName].loadFromFile("sound/" + resourceName);
	}
	return soundMap[resourceName];
}

/*
template <>
sf::Shader& ResourceManager::GetResource(std::string resourceName) {
	if (shaderMap.find(resourceName) == shaderMap.end()) {
		shaderMap[resourceName].loadFromFile()
	}
	return shaderMap[resourceName];
}
*/

template <>
sf::Font& ResourceManager::GetResource(std::string resourceName) {
	if (fontMap.find(resourceName) == fontMap.end()) {
		fontMap[resourceName].loadFromFile("fonts/" + resourceName);
	}
	return fontMap[resourceName];
}
