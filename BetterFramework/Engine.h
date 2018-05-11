#pragma once

#include <map>
#include <stack>
#include <bitset>

#include <SFML/Graphics.hpp>

namespace bf {
	class State;

	class Engine : sf::NonCopyable
	{
	private:
		std::stack<State*> stateStack;
		sf::RenderWindow* window;

		bool shouldCullState;

		// Keyboard / Joystick / Mouse data objects.
		std::bitset<sf::Keyboard::KeyCount> currentInputState;
		std::bitset<sf::Keyboard::KeyCount> prevInputState;

		void CullTopState();

	public:
		// Constructor
		// Pass in a Window width/height in pixels, and optionally a name and a sf::Style.
		// Loads in resources
		Engine(int width, int height, std::string name = "Default Name", sf::Uint32 style = sf::Style::Default);

		// Non copyable
		Engine(const Engine& other) = delete;
		Engine& operator= (const Engine& other) = delete;

		// Destructor
		// Deletes the window
		virtual ~Engine();

		// Start
		// Starts the game loop
		void Start();

		// HandleEvents
		// Handles events such as keypresses, and adds it all to a specific structure.
		void HandleEvents();

		// Returns true if the key was pressed this update loop.
		// For things that should only happen once e.g. pressing esc to open settings (shouldn't loop).
		bool WasKeyPressed(sf::Keyboard::Key k);
		// Returns true if the key is currently being pressed.
		// For things can are continuous e.g. pressing the arrow keys to move.
		bool IsKeyDown(sf::Keyboard::Key k);
		// Returns true if the key was released this update loop
		// For detecting end of keypresses for e.g. charged attacks.
		bool WasKeyReleased(sf::Keyboard::Key k);

		// Adds a state of type StateType to the stack.
		// If not a valid state type, does nothing.
		template <class StateType>
		void AddToStack();

		// Notifies the engine that the top state should be culled on the next update loop.
		// This avoids killing a state while it's in use.
		void SetTopStateToBeCulled();

		// Gets size of the window
		sf::Vector2u GetWindowSize() const;

		// Logging
		enum LogLevel {
			LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_FATAL
		};
		void Log(std::string str);
		void Log(LogLevel level, std::string str);

	private:
		// Logging
		std::map<LogLevel, std::string> _loglevelMessages = {
			{ LOG_ERROR, "[Error]    " },
			{ LOG_FATAL, "[FATAL]    " },
			{ LOG_WARNING, "[Warning]  " },
			{ LOG_INFO, "[Info]     " }
		};
	};


	template <class StateType>
	void Engine::AddToStack() {
		if (!std::is_base_of<State, StateType>::value) {
			Log(LOG_ERROR, "Invalid Template parameter StateType passed into AddToStack()");
			return;
		}
		stateStack.push(new StateType(this));
	}
}