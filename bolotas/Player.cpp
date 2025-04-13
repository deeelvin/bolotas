#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime) {

	this->speed = speed;
	//Set initial texture stage
	row = 0;
	//Flag used to flip the right/left movement animation
	faceRight = true;

	//Set the size of the player shape (Square here)
	body.setSize(sf::Vector2f(100.0f, 100.0f));
	//Set the origin to the center of the shape
	body.setOrigin(body.getSize() / 2.0f);
	//Set the initial position
	body.setPosition({ 100.0f, 100.0f });
	body.setTexture(texture);
}

Player::~Player() {
}

void Player::Update(float deltaTime) {

	//resets the movement so after the key is released the player stops
	sf::Vector2f movement(0.0f, 0.0f);

	//Movement
	//Considering the starting point as 0x, 0y
	//Left is negative X		A
	//Right is positive X		D
	//Up is negative Y		W
	//Down is positive Y		S

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		movement.x += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		movement.y += speed * deltaTime;
	}

	//If the player is "idle" the animation stage should be reset
	//I've commented for now as I preffer that when you stop the character 
	//stays looking to the direction you were facing 
	//The first if handles the horizontal movement and the second the vertical
	if (movement.x == 0.0f) {
		//row = 0;
	}
	else {
		row = 1;

		if (movement.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	if (movement.y < 0.0f) {
		row = 2;
	}
	else if (movement.y > 0.0f) {
		row = 0;
	}

	//Update the animation with the texture row, the interval and the left/right flag
	animation.Update(row, deltaTime, faceRight);
	//With the animation updated, set the correct texture to the player body
	body.setTextureRect(animation.uvRect);
	body.move(movement);

}

void Player::Draw(sf::RenderWindow& window) {

	window.draw(body);

}
