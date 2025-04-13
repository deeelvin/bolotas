#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>
#include "Player.h"

static const sf::Vector2f VIEW_SIZE(800.0f, 600.0f);

// Function to maintain View Aspect Ratio when the window is resized
void ResizeView(const sf::RenderWindow& window, sf::View& view) {

	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize({ VIEW_SIZE.x * aspectRatio, VIEW_SIZE.x });

}

int main() {

	// Window and View creation
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Bolotas", sf::Style::Default);
	window.setFramerateLimit(75);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_SIZE.x, VIEW_SIZE.y));

	//Fps text creation for testing purposes
	sf::Font font("arial.ttf");
	sf::Text fpsText(font);
	fpsText.setString("FPS: ");
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::Red);

	//Player - Just a placeholder for now, as the "bolotas" are going to be AI-driven (just like NPCs) and not controlled "Players"
	//Load the texture of the player
	sf::Texture playerTexture("player.png");
	/*
	Create the player with: texture, image count, switch time, speed
	texture - The texture loaded before
	image count - In this case, the texture has the animation, so 7 frames (columns) with 3 stages (rows)
	switch time - The time each frame of the animation has. 7 frames = 1/7s
	speed - player movement speed
	*/
	Player player(&playerTexture, sf::Vector2u(7, 3), 0.14f, 200.0f);

	//deltaTime for animation and movement
	float deltaTime = 0.0f;
	sf::Clock clock;

	//Clock to calculate fps
	sf::Clock fpsClock;
	float fpsUpdateTime = 0.0f;
	float fps = 0.0f;

	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();

		// Update FPS counter every 0.5 seconds
		fpsUpdateTime += deltaTime;
		if (fpsUpdateTime >= 0.5f) {

			// Current FPS
			fps = 1.0f / deltaTime;
			std::stringstream ss;
			ss << "FPS: " << static_cast<int>(fps);
			fpsText.setString(ss.str());
			fpsUpdateTime = 0.0f;

		}

		//Event Handler
		while (const std::optional evnt = window.pollEvent()) {

			//Close Window Event
			if (evnt->is<sf::Event::Closed>()) {

				window.close();

			}

			//Resize Window Event
			if (evnt->is<sf::Event::Resized>()) {

				//Call to ResizeView function to maintain aspect ratio
				ResizeView(window, view);

			}

		}

		//Update player texture and handle the movement
		player.Update(deltaTime);

		//Set the center of the view to follow the center of the player
		view.setCenter(player.GetPosition());

		//Getting View center and size to position the fps
		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewSize = view.getSize();
		//Position in top-left corner of current view
		fpsText.setPosition({ viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 10 });

		//Clear the view and set Black as the background
		window.clear(sf::Color::Black);
		window.setView(view);
		//Draw the player in the window
		player.Draw(window);
		window.draw(fpsText);
		//Brings the drawn frame to the front buffer (sfml is double buffered)
		window.display();

	}

}