#include "MainState.h"
#include "OtherState.h"

MainState::MainState(bf::Engine* engine): State(engine), shape(20) {
	shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));	
	shape.setPosition(engine->GetWindowSize().x/2.f, engine->GetWindowSize().y/2.f);
}

void MainState::HandleEvents() {
	
}

void MainState::Update(float dt) {
	float xChange = 0;
	float yChange = 0;
	bool up = engine->IsKeyDown(sf::Keyboard::W);
	bool down = engine->IsKeyDown(sf::Keyboard::S);
	bool left = engine->IsKeyDown(sf::Keyboard::A);
	bool right = engine->IsKeyDown(sf::Keyboard::D);

	if (up) yChange -= 8;
	if (down) yChange += 8;
	if (left) xChange -= 8;
	if (right) xChange += 8;

	if (abs(xChange) == abs(yChange)) {
		xChange = xChange / sqrt(2.f);
		yChange = yChange / sqrt(2.f);
	}
	shape.move(xChange, yChange);

}

void MainState::Draw(sf::RenderWindow* window) {
	window->draw(shape);
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/agencyr.ttf");
	sf::Text text{ "State 1",font };
	text.setPosition(450, 550);
	window->draw(text);
}
