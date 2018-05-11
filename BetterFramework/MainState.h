#pragma once
#include "State.h"

class MainState : public bf::State {
	sf::CircleShape shape;
private:

public:
	MainState(bf::Engine* engine);

	void HandleEvents() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow* window) override;
};
