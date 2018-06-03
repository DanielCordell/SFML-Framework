#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceManager
{
private:
	//Resource Storage
	std::map<std::string, sf::Texture> textureMap;
	std::map<std::string, sf::Shader> shaderMap;
	std::map<std::string, sf::Font> fontMap;
	std::map<std::string, sf::SoundBuffer> soundMap;
	std::map<std::string, sf::Music> musicMap;

	ResourceManager() {}
	ResourceManager(ResourceManager const&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	void operator=(ResourceManager const&) = delete;
	void operator=(ResourceManager&&) = delete;
public:
	static ResourceManager* Get();


	template <class R>
	R& GetResource(std::string resourceName);
};


template <>
inline sf::Texture& ResourceManager::GetResource<sf::Texture>(std::string resourceName) {
	if (textureMap.find(resourceName) == textureMap.end()) {
		textureMap[resourceName].loadFromFile("textures/" + resourceName);
	}
	return textureMap[resourceName];
}

template <>
inline sf::Music& ResourceManager::GetResource<sf::Music>(std::string resourceName) {
	if (musicMap.find(resourceName) == musicMap.end()) {
		musicMap[resourceName].openFromFile("music/" + resourceName);
	}
	return musicMap[resourceName];
}

template <>
inline sf::SoundBuffer& ResourceManager::GetResource<sf::SoundBuffer>(std::string resourceName) {
	if (soundMap.find(resourceName) == soundMap.end()) {
		soundMap[resourceName].loadFromFile("sound/" + resourceName);
	}
	return soundMap[resourceName];
}


template <>
inline sf::Font& ResourceManager::GetResource<sf::Font>(std::string resourceName) {
	if (fontMap.find(resourceName) == fontMap.end()) {
		fontMap[resourceName].loadFromFile("fonts/" + resourceName);
	}
	return fontMap[resourceName];
}



template <class R>
R& ResourceManager::GetResource(std::string resourceName) {
	throw std::invalid_argument("Invalid class passed into GetResources when loading " + resourceName);
}
