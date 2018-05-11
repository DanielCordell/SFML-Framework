#include <iostream>
#include <string>

#include "Engine.h"
#include "MainState.h"

namespace bf {

	Engine::Engine(int width, int height, std::string name, sf::Uint32 style){
		window = new sf::RenderWindow(sf::VideoMode(width, height), name);
		stateStack.push(new MainState(this));
		shouldCullState = false;
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
		while (!stateStack.empty()) {
			auto& state = stateStack.top();

			acc += clock.restart().asSeconds();
			while (acc >= frameTime) {
				HandleEvents();
				state->HandleEvents();
				state->Update(frameTime);
				acc -= frameTime;
			}

			window->clear();
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
		prevInputState = currentInputState;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				currentInputState[event.key.code] = true;
			}
			if (event.type == sf::Event::KeyReleased) {
				currentInputState[event.key.code] = false;
			}
		}
	}

	bool Engine::WasKeyPressed(sf::Keyboard::Key k) {
		return currentInputState[k] && !prevInputState[k];
	}

	bool Engine::IsKeyDown(sf::Keyboard::Key k) {
		return currentInputState[k];
	}

	bool Engine::WasKeyReleased(sf::Keyboard::Key k) {
		return !currentInputState[k] && prevInputState[k];
	}

	void Engine::SetTopStateToBeCulled(){
		shouldCullState = true;
	}

	void Engine::Log(std::string str) { Log(LOG_INFO, str); }
	void Engine::Log(LogLevel level, std::string str) {
		std::cout << _loglevelMessages[level] << str << std::endl;
	}

	void Engine::CullTopState() {
		delete stateStack.top();
		stateStack.pop();
	}

	sf::Vector2u Engine::GetWindowSize() const {
		return window->getSize();
	}
}
