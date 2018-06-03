#include <iostream>
#include <string>
#include <filesystem>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Engine.h"
#include "MainState.h"
#include "ResourceManager.h"

namespace fs = std::experimental::filesystem;

namespace bf {

	Engine::Engine(int width, int height, std::string name, sf::Uint32 style){
		window = new sf::RenderWindow(sf::VideoMode(width, height), name);
		stateStack.push(new MainState(this));
		shouldCullState = false;
		ImGui::SFML::Init(*window);
	}

	Engine::~Engine() {
		delete window;

		while (!stateStack.empty()) {
			CullTopState();
		}
	}

	void Engine::Start() {
		sf::Clock clock;
		float acc = 0;
		float frameTime = 1 / 60.f;
		bool firstTime = true;
		while (!stateStack.empty()) {
			auto& state = stateStack.top();

			auto time = clock.restart();
			acc += time.asSeconds();
			while (acc >= frameTime || firstTime) {
				HandleEvents();
				state->HandleEvents();
				state->Update(frameTime);
				acc -= frameTime;
				ImGui::SFML::Update(*window, time);

				SetupGui();

				if (firstTime) firstTime = false;
			}


			window->clear();
			ImGui::SFML::Render(*window);
			state->Draw(window);
			window->display();

			if (shouldCullState) {
				CullTopState();
				shouldCullState = false;
			}
		}
	}

	void Engine::HandleEvents() {
		sf::Event event;
		prevKeyboardState = currentKeyboardState;
		prevMouseState = currentMouseState;
		while (window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::KeyPressed) {
				currentKeyboardState[event.key.code] = true;
			}
			if (event.type == sf::Event::KeyReleased) {
				currentKeyboardState[event.key.code] = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				currentMouseState[event.mouseButton.button] = true;
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				currentMouseState[event.mouseButton.button] = false;
			}
		}
	}

	bool Engine::WasKeyPressed(sf::Keyboard::Key k) {
		return currentKeyboardState[k] && !prevKeyboardState[k];
	}

	bool Engine::IsKeyDown(sf::Keyboard::Key k) {
		return currentKeyboardState[k];
	}

	bool Engine::WasKeyReleased(sf::Keyboard::Key k) {
		return !currentKeyboardState[k] && prevKeyboardState[k];
	}

	bool Engine::WasMousePressed(sf::Mouse::Button m) {
		return currentMouseState[m] && !prevMouseState[m];
	}

	bool Engine::IsMouseDown(sf::Mouse::Button m) {
		return currentMouseState[m];
	}

	bool Engine::WasMouseReleased(sf::Mouse::Button m) {
		return !currentMouseState[m] && prevMouseState[m];
	}

	void Engine::SetTopStateToBeCulled(){
		shouldCullState = true;
	}

	void Engine::Log(std::string str) { Log(LOG_INFO, str); }
	void Engine::Log(LogLevel level, std::string str) {
		std::cout << _loglevelMessages[level] << str << std::endl;
	}

	void Engine::ImportResource(const std::string& item, const std::string& str) {
		auto extension = fs::path(str).extension().string();
		if (item == "Texture") {
			if (Contains(_imageExtensions, extension)) {
				fs::copy_file(str, std::string("Textures/") + fs::path(str).filename().string());
				ResourceManager::Get()->GetResource<sf::Texture>(str);
			}
		}
		else if (item == "Sound") {
			if (Contains(_audioExtensions, extension)) {
				fs::copy_file(str, std::string("Sounds/") + fs::path(str).filename().string());
				ResourceManager::Get()->GetResource<sf::SoundBuffer>(str);
			}
		}
		else if (item == "Music") {
			if (Contains(_audioExtensions, extension)) {
				fs::copy_file(str, std::string("Music/") + fs::path(str).filename().string());
				ResourceManager::Get()->GetResource<sf::Music>(str);
			}
		}
		else if (item == "Shader") {
			if (Contains(_shaderExtensions, extension)) {
				fs::copy_file(str, std::string("Shaders/") + fs::path(str).filename().string());
				ResourceManager::Get()->GetResource<sf::Shader>(str);
			}
		}
		else if (item == "Font") {
			if (Contains(_fontExtensions, extension)) {
				fs::copy_file(str, std::string("Fonts/") + fs::path(str).filename().string());
				ResourceManager::Get()->GetResource<sf::Font>(str);
			}
		}
		else {
			std::string msg = "Invalid Resource argument to ImportResource, " + item;
			Log(LOG_ERROR, msg);
			throw std::invalid_argument(msg);
		}
	}

	void Engine::SetupGui() {
		ImGui::SetNextWindowPos({ 1000,16 });
		ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

		static const char* Items[] = {"Texture", "Sound", "Music",  "Shader", "Font"};
		static int choice = 0;
		ImGui::Text("Choose a type of resource to add...");
		ImGui::ListBox("", &choice ,Items, IM_ARRAYSIZE(Items));
		ImGui::Text("Enter the resource Path");
		static char c[100];
		ImGui::InputText("",c,IM_ARRAYSIZE(c),0);
		if (ImGui::Button("Add Resource")) {
			if (fs::exists(c)) {
				ImportResource(Items[choice], c);
			}
		}
		ImGui::End();

		ImGui::EndFrame();

	}

	bool Contains(std::vector<std::string>& extensions, std::string extension) {
		return find(extensions.begin(), extensions.end(), extension) != extensions.end();
	}

	void Engine::CullTopState() {
		delete stateStack.top();
		stateStack.pop();
	}

	sf::Vector2u Engine::GetWindowSize() const {
		return window->getSize();
	}
}
