#include "MainState.h"
#include "OtherState.h"

MainState::MainState(bf::Engine* engine): State(engine), shape(20), clockDisplayTime(0) {
	shape.setOrigin(20, 20);
	movingText.setPosition(engine->GetWindowSize().x / 2.f, engine->GetWindowSize().y / 2.f);
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

	if (engine->WasMousePressed(sf::Mouse::Left)) {
		float sf = (rand() % 51 - 25) / 25.f + 1;
		shape.setScale(sf, sf);
	}

	if (engine->WasMouseReleased(sf::Mouse::Left)) {
		shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}

	shape.move(xChange, yChange);
	clockDisplayTime += dt;
}

void MainState::Draw(sf::RenderWindow* window) {
	window->draw(shape);
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/agencyr.ttf");
	movingText.setFont(font);
	movingText.move(rand() % 5 - 2, rand() % 5 - 2);
	int timeSecs = floor(clockDisplayTime);
	movingText.setString(std::to_string(timeSecs));
	window->draw(movingText);
}
