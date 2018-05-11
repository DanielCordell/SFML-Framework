#include "MainState.h"
#include "OtherState.h"

OtherState::OtherState(bf::Engine* engine) : State(engine), shape({50,50}) {
	shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	shape.setPosition(engine->GetWindowSize().x / 2.f, engine->GetWindowSize().y / 2.f);
}

void OtherState::HandleEvents() {}

void OtherState::Update(float dt) {
	int xChange = 0;
	int yChange = 0;
	bool up = engine->IsKeyDown(sf::Keyboard::W);
	bool down = engine->IsKeyDown(sf::Keyboard::S);
	bool left = engine->IsKeyDown(sf::Keyboard::A);
	bool right = engine->IsKeyDown(sf::Keyboard::D);

	if (up) yChange -= 20;
	if (down) yChange += 20;
	if (left) xChange -= 20;
	if (right) xChange += 20;

	if (abs(xChange) == abs(yChange)) {
		xChange = xChange / sqrt(2);
		yChange = yChange / sqrt(2);
	}

	shape.move(xChange, yChange);
}

void OtherState::Draw(sf::RenderWindow* window) {
	window->draw(shape);
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/agencyr.ttf");
	sf::Text text{"State 2",font};
	text.setPosition(50, 50);
	window->draw(text);
}
