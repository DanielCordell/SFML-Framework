#pragma once
#include "State.h"

class OtherState : public bf::State {
	sf::RectangleShape shape;
private:

public:
	OtherState(bf::Engine* engine);

	void HandleEvents() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow* window) override;

};
