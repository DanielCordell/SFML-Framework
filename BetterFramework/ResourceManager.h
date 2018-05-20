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

template <class R>
R& ResourceManager::GetResource(std::string resourceName) {
	throw std::invalid_argument("Invalid class passed into GetResources when loading " + resourceName);
}
