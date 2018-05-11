#pragma once
#include <SFML/Graphics.hpp>

#include "Engine.h"

namespace bf {

	class State
	{
	protected:
		Engine* const engine;
	public:
		State(Engine* engine);
		virtual ~State() = default;
		virtual void HandleEvents() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(sf::RenderWindow* window) = 0;
	};

}