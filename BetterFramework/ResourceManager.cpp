#include <SFML/Graphics/Shader.hpp>
#include "ResourceManager.h"

ResourceManager* ResourceManager::Get() {
	static ResourceManager rm;
	return &rm;
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

